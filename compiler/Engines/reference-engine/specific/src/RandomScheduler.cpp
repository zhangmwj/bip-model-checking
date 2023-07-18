/**
 * Copyright Verimag laboratory.
 *
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Braham-Lotfi Mediouni (braham-lotfi.mediouni@univ-grenoble-alpes.fr)
 *
 * This software is a computer program whose purpose is to generate
 * executable code from BIP models.
 *
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 */

#include "RandomScheduler.hpp"
#include <Compound.hpp>
#include <Component.hpp>
#include <InteractionValue.hpp>
#include <Atom.hpp>
#include <AtomInternalPort.hpp>
#include <AtomExternalPort.hpp>
#include <AtomExportPort.hpp>
#include <BipError.hpp>
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <CycleInPrioritiesError.hpp>
#include <CycleInAtomPrioritiesError.hpp>
#include <AtomInvariantViolationError.hpp>
#include <UnexpectedEventError.hpp>
#include <TimeSafetyViolationError.hpp>

#include <Engine.hpp>
#include <Logger.hpp>
#include <StringTree.hpp>

#include <TimingConstraint.hpp>
#include <GlobalClock.hpp>

#include <stdio.h>
#include <stdlib.h>
#include "engine-version.hpp"
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <random>
#include <cmath>
#include <fstream>

#include <time.h>
#include <signal.h>
#include <unistd.h>

// One pseudo random generator per execution
// Reason : discovered weird behavior when sampling very fast
gsl_rng *gen;


RandomScheduler::RandomScheduler(Engine &engine, GlobalClock &clock, Logger &logger, bool debug, bool interactive, bool randomSeed, unsigned int seed, bool asap, bool firstEnabled, bool relaxed) :
  Scheduler(engine),
  mPlatformClock(clock),
  mLogger(logger),
  mDebug(debug),
  mInteractive(interactive),
  mRandomSeed(randomSeed),
  mSeed(seed),
  mAsap(asap),
  mFirstEnabled(firstEnabled),
  mRelaxed(relaxed) {
  // initialize signals management
  RandomScheduler::pid = getpid();
  signal(Engine::SIGBIP, handleSignals);
  signal(SIGALRM, handleSignals);

  // initialize static platform clock
  assert(mStaticPlatformClock == NULL);
  mStaticPlatformClock = &clock;
}

RandomScheduler::~RandomScheduler() {
}

/**
 * \brief Initialize the system.
 */
BipError &RandomScheduler::initialize() {
  // log banner
  logger().log("BIP Engine (version " ENGINE_VERSION " - modified for stochastic behavior)");
  logger().log("");
  logger().log("initialize components...");

  // initialize the seed for random
  ostringstream displayRandomSeed;
  displayRandomSeed << "random scheduling based on seed=";

  if (randomSeed()) {
    int random_seed = time(NULL);
    srand (random_seed);

    displayRandomSeed << random_seed;
  }
  else {
    srand(seed());

    displayRandomSeed << seed();
  }

  // log seed
  logger().log(displayRandomSeed.str());
  logger().log("current update sequence : adding modifications to consider updates of compiler \n");

  BipError &error = engine().initialize();

  logger().log(error);

  return error;
}


// Lotfi

template<typename Out>

void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


std::pair < std::pair < string, string > , std::vector<double> > RandomScheduler::parseDistribution(string distribution){

    string distName, clockName;
    std::vector<double> params;
    std::vector<std::string> x = split(distribution, ',');
    distName = x[0];
    clockName = x[1];

    logStochastic("Distribution name : "+ distName);
    logStochastic("Clock name : " + clockName );
    string messageParams = "With parameters : ";
    string separator = ",";

    // We ignore the last token because it is empty : the distribution string always ends with ','
    if(distName != "custom"){
        for(unsigned int i = 2; i < x.size(); i++){

            double param = ::atof(x[i].c_str());
            messageParams += x[i] + separator;
            params.push_back(param);
        }
    }
    else {
        string noParam = "(none)";
        messageParams += noParam;
    }

    logStochastic(messageParams) ;

    return std::make_pair ( std::make_pair (distName, clockName),params);
}

string RandomScheduler::getDistributionFileName(string distribution){

    string distName, clockName;
    std::vector<double> params;
    std::vector<std::string> x = split(distribution, ',');
    distName = x[0];
    clockName = x[1];


    // We ignore the last token because it is empty : the distribution string always ends with ','
    if(distName == "custom"){
         logStochastic("File name : "+ x[2]);
        return x[2];
    }
    else{
        logStochastic( "Wrong function call !");
        assert(false);
    }

    return "";
}


double get_highest_val(double trunk, vector <double> params, string dist, double coverage){
    if(dist == "normal"){
        return params[0] + gsl_cdf_gaussian_Pinv(coverage, params[1]); // mean + 2 * sigma - trunk; // mean + gsl_cdf_gaussian_Pinv(0.999, sigma) - trunk;
    }
    else if(dist == "exponential"){
        return gsl_cdf_exponential_Pinv(coverage, params[0]);
    }
    else if(dist == "chi_squared"){
        // take a gamma with parameters v/2 and  2 where v is degree of liberty
        return gsl_cdf_gamma_Pinv(coverage, params[0]/2, 2);
    }
    else if(dist == "gamma"){
        return gsl_cdf_gamma_Pinv(coverage, params[0], params[1]);
    }
    return -1;
}

double get_max_proba(double trunk, vector <double> params, string dist){
    if(dist == "normal"){
        return gsl_ran_gaussian_pdf(0, params[1]) ;
    }
    else if(dist == "exponential"){
        return gsl_ran_exponential_pdf(trunk, params[0]) ;
    }
    else if(dist == "chi_squared"){
        // take a gamma with parameters v/2 and  2 where v is degree of liberty
        return gsl_ran_gamma_pdf( (params[0]/2-1)*2, params[0]/2, 2);
    }
    else if(dist == "gamma"){
        // the mode is at (a-1) * b
        return gsl_ran_gamma_pdf( (params[0]-1)*params[1], params[0], params[1]);
    }
    return -1;
}

double get_proba(double value, vector <double> params, string dist){
    if(dist == "normal"){
        return gsl_ran_gaussian_pdf(value - params[0], params[1]) ;
    }
    else if(dist == "exponential"){
        return gsl_ran_exponential_pdf(value, params[0]) ;
    }
    else if(dist == "chi_squared"){
        // take a gamma with parameters v/2 and  2 where v is degree of liberty
        return gsl_ran_gamma_pdf( value, params[0]/2, 2);
    }
    else if(dist == "gamma"){
        return gsl_ran_gamma_pdf( value, params[0], params[1]);
    }
    return -1;
}

double RandomScheduler::truncated_sampling(double trunk, vector <double> params, string dist, double coverage){


    bool found = false;
    double value, proba;
    double val_range = get_highest_val(trunk, params, dist, coverage)  - trunk;
    if(val_range < 0){
        logStochastic(  "Missed deadline ! (value of local clock higher than 0.999 of the distribution support) ");
        assert(false);
    }
//   logStochastic(  "Value range ..." + val_range  );


    double maxi = get_max_proba(trunk, params, dist);
//   logStochastic(  "Max proba ..." + maxi  );

    logStochastic( "Start sampling ..." );
    while(!found){
        double d = gsl_rng_uniform (gen ) ;
//       logStochastic(  "Computed value offset ..." +round(d * val_range) );
        value = trunk + round(d * val_range) ;
//        logStochastic(  "Computed value ..." + value  );
        proba = gsl_rng_uniform (gen)  * (maxi)  ;
//        logStochastic(  "Computed proba ..." + proba  );
        if( get_proba(value, params, dist) >= proba){
            logStochastic(  "Value accepted!" );
            found = true;
        }
        else{
             logStochastic(  "Value rejected!" );
        }
    }
    return value;
}

TimeValue RandomScheduler::sample(string dist, Clock *clk, TimeValue engineTime){

    std::pair < std::pair < string, string > , std::vector<double> > distribution = parseDistribution(dist);

    double coverage = 0.999;

    if(clk->time().getTime() == 0){
        TimeValue tv = TimeValue(0, NANOSECOND);
        if(distribution.first.first == "normal"){
            logStochastic( "Sampling from Gaussian distribution..." ) ;
            if(distribution.second.size() == 2){
                // Maybe we can use the truncated one at 0 here!
                double d = distribution.second[0] + gsl_ran_gaussian(gen,distribution.second[1]);
//                cout << "[Added for debug] Sampled raw value : " << d << endl;

                int t = std::round(d);
                if(t<0) t = 0;
                tv = TimeValue(t + engineTime.getTime(), NANOSECOND);
                return tv;
            }
            else{
                logStochastic( "Wrong number of parameters: Using default parameters (5,2)") ;
                int t = std::round(5 + gsl_ran_gaussian(gen, 2));
                if(t<0) t = 0;
                tv = TimeValue(t+ engineTime.getTime(), NANOSECOND);
                return tv;
            }
         }
         else if(distribution.first.first == "exponential"){
           logStochastic( "Sampling from exponential distribution...") ;
            if(distribution.second.size() == 1){
                // Maybe we can use the truncated one at 0 here!
                int t = std::round( gsl_ran_exponential(gen,distribution.second[0]));
                if(t<0) t = 0;
                tv = TimeValue(t + engineTime.getTime(), NANOSECOND);
                return tv;
            }
            else{
                logStochastic( "Wrong number of parameters: Using default parameter (1)") ;
                int t = std::round(gsl_ran_exponential(gen, 1));
                if(t<0) t = 0;
                tv = TimeValue(t+ engineTime.getTime(), NANOSECOND);
                return tv;
            }
         }
         else if(distribution.first.first== "chi_squared" ){
            logStochastic("Sampling from chi_squared distribution..." );
            if(distribution.second.size() == 1){
                // Maybe we can use the truncated one at 0 here!
                int t = std::round( gsl_ran_gamma(gen,distribution.second[0]/2, 2));
                if(t<0) t = 0;
                tv = TimeValue(t + engineTime.getTime(), NANOSECOND);
                return tv;
            }
            else{
                logStochastic( "Wrong number of parameters. Using default parameters (2)");
                int t = std::round(gsl_ran_gamma(gen,2/2, 2));
                if(t<0) t = 0;
                tv = TimeValue(t+ engineTime.getTime(), NANOSECOND);
                return tv;
            }
         }
         else if(distribution.first.first== "gamma"){
            logStochastic("Sampling from Gamma distribution...") ;
            if(distribution.second.size() == 2){
                // Maybe we can use the truncated one at 0 here!
                int t = std::round(gsl_ran_gamma(gen,distribution.second[0], distribution.second[1]));
                if(t<0) t = 0;
                tv = TimeValue(t + engineTime.getTime(), NANOSECOND);
                return tv;
            }
            else{
                logStochastic( "Wrong number of parameters. Using default parameters (2,3)") ;
                int t = std::round(gsl_ran_gamma(gen,2, 3));
                if(t<0) t = 0;
                tv = TimeValue(t+ engineTime.getTime(), NANOSECOND);
                return tv;
            }
         }
         else if(distribution.first.first== "uniform"){
            logStochastic( "Sampling from uniform distribution..." );
            if(distribution.second.size() == 2){
                if(distribution.second[0] <= distribution.second[1]){
                    int t = std::round(gsl_rng_uniform(gen) * (distribution.second[1] - distribution.second[0]) + distribution.second[0]);
                    if(t<0) t = 0;
                    tv = TimeValue(t + engineTime.getTime(), NANOSECOND);
                    return tv;
                }
                else{
                    logStochastic( "Wrong parameters. Using default parameters (0,10)") ;
                    int t = std::round(gsl_rng_uniform(gen) * 10);
                    if(t<0) t = 0;
                    tv = TimeValue(t + engineTime.getTime(), NANOSECOND);
                    return tv;
                }
            }
            else{
                logStochastic( "Wrong number of parameters. Using default parameters (0,10)") ;
                int t = std::round(gsl_rng_uniform(gen) * 10);
                if(t<0) t = 0;
                tv = TimeValue(t + engineTime.getTime(), NANOSECOND);
                return tv;
            }
         }
         else if(distribution.first.first== "custom"){
            logStochastic("Sampling from custom distribution...");
            string fileName = getDistributionFileName(dist);


            std::ifstream ifile(fileName, std::ios::in);
            std::map<double,double> dist;

            //check to see that the file was opened correctly:
            if (!ifile.is_open()) {
                std::cout << "There was a problem opening the input file!\n";
                assert(false);
            }

            double prob = 0.0, time = 0.0;
            double mem_prob = -1.0, mem_time = -1.0;
            while (ifile >> time && ifile >> prob) {
                dist.insert(std::pair<double, double>(prob,time));
                assert(time >= 0 && prob >= 0 && prob <= 1 && time > mem_time && prob > mem_prob);
                mem_time = time;
                mem_prob = prob;
            }

            double d = gsl_rng_uniform(gen);
            std::map<double, double>::iterator iter;
            iter = dist.lower_bound(d);
            int t = std::round(iter->second);
            if(t<0) t = 0;
            tv = TimeValue(t + engineTime.getTime(), NANOSECOND);
            return tv;


         }
         else{
            logStochastic( "Error : unknown distribution ");
            assert(false);
         }

        return tv;
    }
    else{
        // Shift and normalize then sample
        TimeValue tv = TimeValue(0, NANOSECOND);

        double trunk = clk->time().getTime();
        double val_range = get_highest_val(trunk, distribution.second, distribution.first.first, coverage)  - trunk;
        if(val_range < 0){
            logStochastic(  "Missed deadline ! (value of local clock higher than 0.999 of the distribution support) ");
            logStochastic( "Resetting stochastic clock and sampling from original distribution" );
            //Reset stochastic clock
            clk->resetTo(tv);
            // Sample from original distribution
            return sample(dist, clk, engineTime);

        }


        if(distribution.first.first == "normal"){

            logStochastic("Sampling from truncated Gaussian distribution..." ) ;
            if(distribution.second.size() == 2){
                int t = std::round(truncated_sampling(trunk, distribution.second, distribution.first.first, coverage ));
//                cout << "Actual value of local clock " << clk->time().getTime() << endl;
//                cout << "Generated value of local clock " << t << endl;
                assert(t >= trunk) ;
                tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                return tv;
            }
            else{
               logStochastic( "Wrong number of parameters. Using default parameters (5,2)") ;
                std::vector <double> params;
                params.push_back(5);// Default Mu
                params.push_back(2);// Default Sigma
                int t = std::round(truncated_sampling(trunk, params, distribution.first.first, coverage ));
                assert(t>=trunk) ;
                tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                return tv;
            }
         }
         else if(distribution.first.first == "exponential"){

            logStochastic("Sampling from truncated exponential distribution..." ) ;
            if(distribution.second.size() == 1){
                int t = std::round(truncated_sampling(trunk, distribution.second, distribution.first.first, coverage ));
//                cout << "Actual value of local clock " << clk->time().getTime() << endl;
//                cout << "Generated value of local clock " << t << endl;
                assert(t >= trunk) ;
                tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                return tv;
            }
            else{
                logStochastic( "Wrong number of parameters. Using default parameters (1)");
                std::vector <double> params;
                params.push_back(1);// Default Mu
                int t = std::round(truncated_sampling(trunk, params, distribution.first.first, coverage ));
                assert(t>=trunk) ;
                tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                return tv;
            }
         }

         else if(distribution.first.first== "chi_squared" ){
            logStochastic("Sampling from truncated chi_squared distribution..." ) ;
            if(distribution.second.size() == 1){
                int t = std::round(truncated_sampling(trunk, distribution.second, distribution.first.first, coverage ));
//                cout << "Actual value of local clock " << clk->time().getTime() << endl;
//                cout << "Generated value of local clock " << t << endl;
                assert(t >= trunk) ;
                tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                return tv;
            }
            else{
                logStochastic( "Wrong number of parameters. Using default parameters (2)") ;
                std::vector <double> params;
                params.push_back(2);// Default degree of liberty
                int t = std::round(truncated_sampling(trunk, params, distribution.first.first, coverage ));
                assert(t>=trunk) ;
                tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                return tv;
            }
         }

         else if(distribution.first.first== "gamma"){
            logStochastic("Sampling from truncated Gamma distribution..." ) ;
            if(distribution.second.size() == 2){
                int t = std::round(truncated_sampling(trunk, distribution.second, distribution.first.first, coverage ));
//                cout << "Actual value of local clock " << clk->time().getTime() << endl;
//                cout << "Generated value of local clock " << t << endl;
                assert(t >= trunk) ;
                tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                return tv;
            }
            else{
                logStochastic( "Wrong number of parameters. Using default parameters (5,2)") ;
                std::vector <double> params;
                params.push_back(2);// Shape param
                params.push_back(3);// Scale param
                int t = std::round(truncated_sampling(trunk, params, distribution.first.first, coverage ));
                assert(t>=trunk) ;
                tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                return tv;
            }
         }

         else if(distribution.first.first== "uniform"){
            cout << "Sampling from truncated uniform distribution..." << endl ;
            if(distribution.second.size() == 2){
                if(clk->time().getTime()<= distribution.second[1]){
                    if(distribution.second[0] <= distribution.second[1]){
                        double a =  (clk->time().getTime() < distribution.second[0] ? distribution.second[0] : clk->time().getTime()) ;
                        int t = std::round(gsl_rng_uniform(gen) * (distribution.second[1] - a ) + a);
                        if(t<0) t = 0;
                        tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                        return tv;
                    }
                    else{
                        logStochastic( "Wrong parameters. Using default parameters (current_time,10)");
                        int t = std::round(gsl_rng_uniform(gen) * (10- clk->time().getTime()) + clk->time().getTime() );
                        if(t<0) t = 0;
                        tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                        return tv;
                    }
                }
                else{
                     std::cout << "Error : missed deadline ! ";
                     assert(false);
                }
            }
            else{
                logStochastic( "Wrong number of parameters. Using default parameters (current_time,10)") ;
                int t = std::round(gsl_rng_uniform(gen) * (10- clk->time().getTime()) + clk->time().getTime() );
                if(t<0) t = 0;
                tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
                return tv;
            }
         }
         else if(distribution.first.first== "custom"){
             logStochastic( "Sampling from truncated custom distribution...") ;
             string fileName = getDistributionFileName(dist);


            std::ifstream ifile(fileName, std::ios::in);
            std::map<double,double> dist;

            //check to see that the file was opened correctly:
            if (!ifile.is_open()) {
                std::cerr << "There was a problem opening the input file! ";
                assert(false);
            }

            double prob = 0.0, time = 0.0;
            double mem_prob = -1.0, mem_time = -1.0;
            double max_p = 0.0;
            while (ifile >> time && ifile >> prob) {
                if(time < clk->time().getTime()){
                    if(max_p < prob) max_p = prob;
                }
                else dist.insert(std::pair<double, double>(prob - max_p,time));

                assert(time >= 0 && prob >= 0 && prob <= 1 && time > mem_time && prob > mem_prob);
                mem_time = time;
                mem_prob = prob;
            }

            if( dist.empty() == true ){
                std::cout << "Error : missed deadline ! ";
                assert(false);
            }

            double d = gsl_rng_uniform(gen) * (1 - max_p);
            std::map<double, double>::iterator iter;
            iter = dist.lower_bound(d);
            int t = std::round(iter->second);
            if(t<0) t = 0;
            assert (t  - clk->time().getTime()>= 0);
            tv = TimeValue(t + engineTime.getTime() - clk->time().getTime(), NANOSECOND);
            return tv;


         }
         else{
            cout << "Error : unknown distribution ";
            assert(false);
         }
        return tv;
    }

}


/**
 * \brief Execute a single execution sequence randomly.
 *
 * Interactions and internal ports are chosen randomly according to
 * a uniform repartition of the probability. It is based on rand() of
 * the standard library for computing random values. Notice that the
 * seed for rand() is currently not fixed.
 */


BipError &RandomScheduler::run() {

    gsl_rng_env_setup();
    const gsl_rng_type* type = gsl_rng_default;   // Default algorithm 'twister'
    gen = gsl_rng_alloc (type);
    gsl_rng_set (gen, time(NULL));


  logger().log( "Random Scheduler Running");
  TimeValue timeSafetyViolation = TimeValue::MAX;

  if (debug()) {
    print();
  }

  // check time-safety violation and update model time
  BipError &error = checkTimeSafetyAndResume();
  logger().log(error);

  if (error.type() != NO_ERROR) {
    return error;
  }

  // Lotfi
     if(printVariables) print_vars();


  while (!deadlock() && !logger().reachedLimit()) {

    cout << endl ;

    // take a snapshot of the treated notifications
    resetNotifications();

    // /!\ order is critical: must be placed after updateTreatedNotifications()!
    // update current status of external ports w.r.t. incoming events
    BipError &errorInCheckExternals = engine().checkExternals();
    logger().log(errorInCheckExternals);

    if (errorInCheckExternals.type() != NO_ERROR) {
      return errorInCheckExternals;
    }

    // choose an interaction / internal port / external port
    BipError &errorInChoose = choose();
    logger().log(errorInChoose);

    if (errorInChoose.type() != NO_ERROR) {
      return errorInChoose;
    }

    // wait for the next event
    bool hasNotifications = waitForNotificationsUntil(wakeUpTime());

    if (hasNotifications) {
      continue;
    }
    else if (!hasChosen() && !hasNotifications) {
      timeSafetyViolation = wakeUpTime();
      break;
    }
    else if (hasChosen() && !hasNotifications) {
      // execute the selected interaction / internal port / external port
      // Begin update
      logStochastic(logMemory());
      // End update
      if (hasChosenInteraction()) {
        if (!interactive()) logger().logEnabled();
        logger().log(chosenInteraction(), wakeUpTime());

        //Begin update
        cleanMemory(chosenInteraction());
        //End update

        BipError &error = engine().execute(chosenInteraction(), wakeUpTime());
        logger().log(error);

        if (error.type() != NO_ERROR) {
          return error;
        }
      }
      else if (hasChosenInternal()) {
        if (!interactive()) logger().logEnabled();
        logger().log(chosenInternal(), wakeUpTime());
        BipError &error = engine().execute(chosenInternal(), wakeUpTime());
        logger().log(error);

        //Begin update
        cleanMemory(chosenInternal());
        //End update


        if (error.type() != NO_ERROR) {
          return error;
        }
      }
      else if (hasChosenExternal()) {
        logger().logEnabledExternals();
        logger().log(chosenExternal(), wakeUpTime());
        BipError &error = engine().execute(chosenExternal(), wakeUpTime());
        logger().log(error);

        //Begin update
        cleanMemory(chosenExternal());
        //End update

        if (error.type() != NO_ERROR) {
          return error;
        }
      }
      else {
        assert(false);
      }


      // Lotfi
      if(printVariables) print_vars();




      if (debug()) {
        print();
      }

      // check time-safety violation and update model time
      BipError &error = checkTimeSafetyAndResume();
      logger().log(error);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
    else {
      assert(false);
    }
  }

  // log deadlock or reached limit
  logger().logEnabled();


    gsl_rng_free (gen);
  return BipError::NoError;
}



BipError &RandomScheduler::choose() {
  // reninitialize choosing related values
  mChosenInteraction = NULL;
  mChosenInternal = NULL;
  mChosenExternal = NULL;

  mWakeUpTime = engine().waitInterval().right();
  mMinCriterion = TimeValue::MAX;
  mNbMinCriterion = 0;

  // interactive choice
  BipError &error = chooseInteractive();

  // choose if no choice has been made by the interactive mode
  if (error.type() == NO_ERROR && !hasChosenInteraction() && !hasChosenInternal()) {
  //My code begin
  std::set<const Connector *> enabledInteractions;
  std::set<const AtomInternalPort *> enabledInternals;
  std::set<const AtomExternalPort *> enabledExternals;
  //End my code
  //cout << endl << endl;

    for (vector<InteractionValue *>::const_iterator interactionIt = engine().interactions().begin() ;
         interactionIt != engine().interactions().end() ;
         ++interactionIt) {
      InteractionValue &interaction = **interactionIt;

//        AtomInternalPort *port = interaction.getStochasticPort();
//      cout << ">>>>>  Distribution : " << port->getDistribution() << endl;
//      cout << ">>>>>  Clock Value : " << port->getClock()->time().getTime() << endl;
      choose(interaction);
      // Added line
      enabledInteractions.insert(&(interaction.connector()));
    }
    cleanMemory(enabledInteractions);

    for (vector<AtomInternalPort *>::const_iterator portIt = engine().internals().begin() ;
         portIt != engine().internals().end() ;
         ++portIt) {
      AtomInternalPort &port = **portIt;
      choose(port);
      // Added line
      enabledInternals.insert(&port);
    }
    cleanMemory(enabledInternals);

    for (vector<AtomExternalPort *>::const_iterator portIt = engine().externals().begin() ;
         portIt != engine().externals().end() ;
         ++portIt) {
      AtomExternalPort &port = **portIt;
      //Commented line : Interval interv = engine().interval(port);
      choose(port);
      // Added line
      enabledExternals.insert(&port);
    }
    cleanMemory(enabledExternals);

  }



  return error;
}


BipError &RandomScheduler::chooseInteractive() {
  if (interactive()) {
    bool cont = true;

    while ((!engine().interactions().empty() || !engine().internals().empty()) && engine().externals().empty() && cont) {
      logger().logEnabled();
      ostringstream oss;
      oss << engine().interactions().size() + engine().internals().size() - 1;
      string message = " -> enter interaction / internal port number (0.." + oss.str() + "), or 'r' for a random choice: ";

      logger().log(message);

      string str;
      cout.flush();
      cin >> str;

      if (cin.eof()) { // in case of ctrl-D
        cout << endl;
        exit(0);
      }
      else if (str.size() > 0) {
        if (str[0] != 'r') {
          unsigned int chosenIndex;
          istringstream iss( str );
          iss >> chosenIndex;

          if (iss.fail() || chosenIndex >= engine().interactions().size() + engine().internals().size()) {
            logger().log("Invalid choice!");
            cont = true;
          }
          else {
            TimeValue currentTime = platformClock().time();

            cont = true;

            if (chosenIndex < engine().interactions().size()) {
              InteractionValue *chosen = engine().interactions()[chosenIndex];
              Interval interval = engine().interval(*chosen);
              interval &= Interval(currentTime, TimeValue::MAX);

              if (!interval.empty()) {
                mChosenInteraction = chosen;
                mWakeUpTime = plan(interval);
                cont = false;
              }
            }
            else {
              AtomInternalPort *chosen = engine().internals()[chosenIndex - engine().interactions().size()];
              Interval interval = engine().interval(*chosen);
              interval &= Interval(currentTime, TimeValue::MAX);

              if (!interval.empty()) {
                mChosenInternal = chosen;
                mWakeUpTime = plan(interval);
                cont = false;
              }
            }

            if (cont) {
              BipError &error = checkTimeSafety();

              if (error.type() != NO_ERROR) {
                return error;
              }
            }
          }
        }
      }
    }
  }

  return BipError::NoError;
}

bool RandomScheduler::choose(InteractionValue &interaction) {
  bool ret = false;
//Begin My code
string logMessage = "Planning date for interaction "+interaction.connector().name() + "... ";

 Interval interv = Interval(engine().time(), TimeValue::MAX);
 TimingConstraint constraint = interaction.timingConstraint();
 if(constraint.urgency() == LAZY){
    int proba = rand()%100;
    if(proba < 50){
        logMessage += "Lazy interaction ignored!" ;
        cleanMemory(interaction);
        logStochastic(logMessage);
        logStochastic("");
        return ret;
    }
 }


logStochastic(logMessage);
TimeValue t;
AtomInternalPort *stochPort = interaction.getStochasticPort();

// In the case stochastic, the interval of the memory encodes the value of the stochastic clock on the left bound and the value of the global clock on the right bound,
// at the moment of sampling
if(stochPort!=NULL){
      if(!isMemorized(&(interaction.connector()))){
        if(constraint.urgency() == EAGER) t = engine().time();
        else t = sample(stochPort->getDistribution(), stochPort->getClock(), engine().time()) ;
        Interval interv = Interval(TimeValue(stochPort->getClock()->time().getTime() ,NANOSECOND), engine().time());
        insertMemory(&(interaction.connector()),t, interv);
      }
      else{
        Interval interv = getMemoryInterval(&(interaction.connector()));
        if( (stochPort->getClock()->time().getTime() - interv.left().getTime()) == (engine().time().getTime() - interv.right().getTime() ) ){
            if(printStochTrace )  cout <<  "[STOCHASTIC RT-BIP ENGINE]: Planned date from memory." <<   endl;
            t = getMemoryTime(&(interaction.connector()));
        }
        else{
            if(constraint.urgency() == EAGER) t = engine().time();
            else t = sample(stochPort->getDistribution(), stochPort->getClock(), engine().time());
            Interval interv = Interval(TimeValue(stochPort->getClock()->time().getTime() ,NANOSECOND), engine().time());
            insertMemory(&(interaction.connector()),t, interv);
        }
      }
 }
 else
 {

     Interval intervConstraint = constraint.interval();
     interv &= constraint.interval();
     interv &= engine().getTop().invariant();

     if(printStochTrace){
        cout <<"[STOCHASTIC RT-BIP ENGINE]: Timing constraint : " << constraint ;
        cout << " Time : " << engine().time() ;
        cout << " Interval : " << interv << endl ;
     }


    // Old code :  Interval interv = engine().interval(interaction);

      if(!isMemorized(&(interaction.connector()))){
        if(constraint.urgency() == EAGER) t = interv.next(engine().time());
        else t = plan(interv);
        insertMemory(&(interaction.connector()),t, intervConstraint);
      }
      else{
        if(getMemoryInterval(&(interaction.connector())) == intervConstraint){
            if(printStochTrace )  cout <<  "[STOCHASTIC RT-BIP ENGINE]: Planned date from memory." <<   endl;
            t = getMemoryTime(&(interaction.connector()));
        }
        else{
            if(constraint.urgency() == EAGER) t = interv.next(engine().time());
            else t = plan(interv);
            insertMemory(&(interaction.connector()),t, intervConstraint);
        }
      }

  }
  if(printStochTrace )  cout <<  "[STOCHASTIC RT-BIP ENGINE]: Planned date : " << t << endl;

 //End my code

  if (choose(interv, t, false)) {
    mChosenInteraction = &interaction;
    mChosenInternal = NULL;
    mChosenExternal = NULL;

    ret = true;
  }


logStochastic("");
  return ret;
}

bool RandomScheduler::choose(AtomInternalPort &internal) {
  bool ret = false;


  //Begin My code
  if(printStochTrace) cout << "[STOCHASTIC RT-BIP ENGINE]: Planning date for internal port " << internal.name()<< "... ";
 Interval interv = Interval(engine().time(), TimeValue::MAX);
 TimingConstraint constraint = internal.timingConstraint();
 if(constraint.urgency() == LAZY){
    int proba = rand()%100;
    if(proba < 50){
        if(printStochTrace) cout << "Lazy internal ignored!" << endl;
        logStochastic("");
        cleanMemory(internal);
        return ret;
    }
 }

 if(printStochTrace) cout << endl;

   TimeValue t;
 if(internal.getDistribution()!=""){
        if(internal.timingConstraint().interval().left() != TimeValue::MIN || internal.timingConstraint().interval().right() != TimeValue::MAX){
            cout << "[STOCHASTIC RT-BIP ENGINE]: Fatal Error! Port " << internal.name() << " of type stochastic cannot have a timing constraint! ";
            assert(false);
        }

      if(!isMemorized(&internal)){
        if(constraint.urgency() == EAGER) t = engine().time();
        else t = sample(internal.getDistribution(), internal.getClock(), engine().time()) ;
        Interval interv = Interval(TimeValue(internal.getClock()->time().getTime() ,NANOSECOND), engine().time());
        insertMemory(&internal,t, interv);
      }
      else{
        Interval interv = getMemoryInterval(&internal);
        if( (internal.getClock()->time().getTime() - interv.left().getTime()) == (engine().time().getTime() - interv.right().getTime() ) ){
           if(printStochTrace )  cout <<  "[STOCHASTIC RT-BIP ENGINE]: Planned date from memory." <<   endl;
            t = getMemoryTime(&internal);
        }
        else{
            if(constraint.urgency() == EAGER) t = engine().time();
            else t = sample(internal.getDistribution(), internal.getClock(), engine().time());
            Interval interv = Interval(TimeValue(internal.getClock()->time().getTime() ,NANOSECOND), engine().time());
            insertMemory(&internal,t, interv);
        }
      }
 }
 else
 {



 Interval intervConstraint = constraint.interval();
 interv &= constraint.interval();
 interv &= engine().getTop().invariant();

 if(printStochTrace){
    cout << "[STOCHASTIC RT-BIP ENGINE]: Timing constraint : " << constraint ;
    cout << " Time : " << engine().time() ;
    cout << " Interval : " << interv << endl;
 }

// Old code :  Interval interv = engine().interval(interaction);

  if(!isMemorized(&internal)){
    if(constraint.urgency() == EAGER) t = interv.next(engine().time());
    else t = plan(interv);
    insertMemory(&internal,t, intervConstraint);
  }
  else{

    if(getMemoryInterval(&internal) == intervConstraint){
        if(printStochTrace )  cout <<  "[STOCHASTIC RT-BIP ENGINE]: Planned date from memory." <<   endl;
         t = getMemoryTime(&internal);
    }
    else{
        if(constraint.urgency() == EAGER) t = interv.next(engine().time());
        else t = plan(interv);
        insertMemory(&internal,t, intervConstraint);
    }
  }
  }
  if(printStochTrace) cout << "[STOCHASTIC RT-BIP ENGINE]: Planned date : " << t << endl;
 //End my code




  if (choose(interv, t, false)) {
    mChosenInteraction = NULL;
    mChosenInternal = &internal;
    mChosenExternal = NULL;

    ret = true;
  }
  logStochastic("");
  return ret;
}

bool RandomScheduler::choose(AtomExternalPort &external) {
  bool ret = false;

   //Begin My code

 Interval interv = Interval(engine().time(), TimeValue::MAX);
 TimingConstraint constraint = external.timingConstraint();
 if(constraint.urgency() == LAZY){
    int proba = rand()%100;
    if(proba < 50){
        if(printStochTrace){
            cout << "[STOCHASTIC RT-BIP ENGINE]: Planning date for external port "<< external.name() << "... ";
            cout << "Lazy external ignored!" << endl;
        }
        cleanMemory(external);
        logStochastic("");
        return ret;
    }
 }


 Interval intervConstraint = constraint.interval();
 interv &= constraint.interval();
 interv &= engine().getTop().invariant();

 if(printStochTrace){
    cout << "[STOCHASTIC RT-BIP ENGINE]: Planning date for external port "<< external.name() << "... ";
    cout << "Timing constraint : " << constraint ;
    cout << " Time : " << engine().time() ;
    cout << " Interval : " << interv << endl;
 }

// Old code :  Interval interv = engine().interval(interaction);
  TimeValue t;
  if(!isMemorized(&external)){
    if(constraint.urgency() == EAGER) t = interv.next(engine().time());
    else t = plan(interv);
    insertMemory(&external,t, intervConstraint);
  }
  else{

    if(getMemoryInterval(&external) == intervConstraint){
        if(printStochTrace )  cout <<  "[STOCHASTIC RT-BIP ENGINE]: Planned date from memory." <<   endl;
         t = getMemoryTime(&external);
    }
    else{
        if(constraint.urgency() == EAGER) t = interv.next(engine().time());
        else t = plan(interv);
        insertMemory(&external,t, intervConstraint);
    }
  }
  if(printStochTrace) cout << "[STOCHASTIC RT-BIP ENGINE]: Planned date : " << t << endl;
 //End my code

  if (choose(interv, t, hasChosenInteraction() || hasChosenInternal())) {
    mChosenInteraction = NULL;
    mChosenInternal = NULL;
    mChosenExternal = &external;

    ret = true;
  }

  logStochastic("");
  return ret;
}

bool RandomScheduler::hasChosen() const {
  return hasChosenInteraction() ||
         hasChosenInternal()    ||
         hasChosenExternal();
}

/**
 * \brief
 *
 *
 * \param
 *
 * \return
 */
 bool RandomScheduler::choose(const Interval &interval, const TimeValue &plannedTime, bool hasPriority) {
  bool ret = false;

  TimeValue criterion = schedulingCriterion(interval, plannedTime);

  if (criterion < mMinCriterion || (criterion == mMinCriterion && hasPriority)) {
    // found a new minimum for the criterion
    mMinCriterion = criterion;
    mNbMinCriterion = 1;

    ret = true;
  }
  else if (criterion == mMinCriterion) {
    ++mNbMinCriterion;

    // random choice between whose which minimize the criterion
    if ((unsigned int) (mNbMinCriterion * (rand() / (RAND_MAX + 1.0))) == mNbMinCriterion - 1) {
      ret = true;
    }
  }

  if (ret) {
    mWakeUpTime = plannedTime;
  }

  return ret;
}

/**
 * \brief Chose an execution time meeting a given timing constraint.
 *
 * The choice is made according to the selected scheduling policy,
 * i.e. ASAP or random.
 *
 * \param interval is the target interval.
 *
 * \return a time value meeting the timing constraint.
 */
TimeValue RandomScheduler::plan(const Interval &interval) const {
  TimeValue ret;
//Original cade is commented
//  if (asap()) {
//    ret = interval.next(engine().time());
//  }
//  else {
    ret = interval.random(TimeValue(1, NANOSECOND));
//  }

  return ret;
}

/**
 * \brief Criterion the scheduler should minimize.
 *
 * In the case of firstEnabled scheduling policy,
 * the criterion is the next time value that belong
 * to the target interval from the current time,
 * otherwise it is the planned execution time.
 *
 * \param interval is the validity interval of the target
 * interaction / internal port / external port to schedule.
 * \param planned is the planned time for execution of the
 * target interaction / internal port / external.
 *
 * \return the time value defining the scheduling
 * criterion to be minimized.
 */
TimeValue RandomScheduler::schedulingCriterion(const Interval &interval, const TimeValue &planned) const {
  TimeValue ret = TimeValue::MAX;

  if (firstEnabled()) {
    ret = interval.next(engine().time());
  }
  else {
    ret = planned;
  }

  return ret;
}

/**
 * \brief Update model time w.r.t. actual time and check that such an
 * update meets timing constraints (urgency, invariants).
 * a useful report to the user (e.g. error message, etc.).
 *
 * \return false if the update of the model time satisfied the timing
 * constraints.
 */
BipError &RandomScheduler::checkTimeSafety() {
  TimeValue ret = TimeValue::MAX;

  // skip it if relaxed and current time = next deadline
  if (!relaxed() || engine().time() < engine().waitInterval().right()) {
    TimeValue currentTime = platformClock().time();

    if (!engine().waitInterval().in(currentTime)) {
      TimeSafetyViolationError &error = *new TimeSafetyViolationError(currentTime);

      return error;
    }
    else {
      engine().wait(currentTime);
    }
  }

  return BipError::NoError;
}

/**
 * \brief Update model time w.r.t. actual time and check that such an
 * update meets timing constraints (urgency, invariants).
 * a useful report to the user (e.g. error message, etc.).
 *
 * \return false if the update of the model time satisfied the timing
 * constraints.
 */
BipError &RandomScheduler::checkTimeSafetyAndResume() {
  TimeValue ret = TimeValue::MAX;

  // skip it if relaxed and current time = next deadline
  if (!relaxed() || engine().time() < engine().waitInterval().right()) {
    TimeValue currentTime = platformClock().time();

    if (!engine().resumeInterval().in(currentTime)) {
      TimeSafetyViolationError &error = *new TimeSafetyViolationError(currentTime);

      return error;
    }
    else {
      BipError &error = engine().resume(currentTime);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
  }

  return BipError::NoError;
}

bool RandomScheduler::deadlock() const {
  return engine().interactions().empty() && // interaction to execute
         engine().internals().empty()    && // internal port to execute
         engine().externals().empty()    && // external port to execute
    (engine().waiting().empty() || platformClock().time() > engine().waitInterval().right());        // external port waiting
}

bool RandomScheduler::waitForNotificationsUntil(const TimeValue &time) {
  bool ret = false;

  sigset_t maskOld, maskSIGBIP;

  sigemptyset(&maskSIGBIP);
  sigaddset(&maskSIGBIP, Engine::SIGBIP);

  sigprocmask(SIG_BLOCK, &maskSIGBIP, &maskOld);

  if (hasNotifications()) {
    ret = true;
  }
  else {
    ret = platformClock().wait(time);
  }

  sigprocmask(SIG_UNBLOCK, &maskSIGBIP, NULL);

  return ret;
}

void RandomScheduler::notify() {
  kill(RandomScheduler::pid, Engine::SIGBIP);
}

pid_t RandomScheduler::pid(0);

GlobalClock *RandomScheduler::mStaticPlatformClock(NULL);

volatile unsigned int RandomScheduler::mNbReceivedNotifications(0);

void RandomScheduler::handleSignals(int signum) {
  if (signum == Engine::SIGBIP) {
    mNbReceivedNotifications++;
  }
}


/**
 * \brief Displays the current state of the system.
 *
 * Useful for debug purpose. Side effect on cout.
 */
void RandomScheduler::print() {
  const Engine &constEngine = engine();
  const Compound &top = constEngine.top();

  StringTree debugStrTree = print(top);
  string header = "[BIP ENGINE]: ";
  string debugStr = debugStrTree.toString(header);
  cout << debugStr;
}

StringTree RandomScheduler::print(const ConnectorExportPort &port) {
  StringTree ret(port.name());

  for (unsigned int i = 0 ; i < port.portValues().size() ; ++i) {
    string portStr = port.portValues()[i]->toString();

    if (portStr.size() == 0) {
      string noValueStr = "<no_value>";
      ret.addChild(noValueStr);
    }
    else {
      ret.addChild(portStr);
    }
  }

  return ret;
}

StringTree RandomScheduler::print(const CompoundExportPort &port) {
  StringTree ret(port.name());

  for (unsigned int i = 0 ; i < port.portValues().size() ; ++i) {
    string portStr = port.portValues()[i]->toString();

    if (portStr.size() == 0) {
      string noValueStr = "<no_value>";
      ret.addChild(noValueStr);
    }
    else {
      ret.addChild(portStr);
    }
  }

  return ret;
}

StringTree RandomScheduler::print(const AtomInternalPort &port) {
  string ret = port.name();

  if (port.hasPortValue()) {
    string portStr = port.portValue().toString();

    if (portStr.size() > 0) {
      ret = ret + " (" + portStr + ")";
    }
    else {
      ret = ret + " (<no_value>)";
    }

    if (port.portValue().hasInterval()) {
      ostringstream oss;

      oss << TimingConstraint(port.portValue().urgency(), port.portValue().interval());

      ret = ret + " " + oss.str();
    }
    else if (port.portValue().urgency() != LAZY) {
      ostringstream oss;

      oss << TimingConstraint(port.portValue().urgency(), Interval(TimeValue::MIN, TimeValue::MAX));

      ret = ret + " " + oss.str();
    }
  }

  return StringTree(ret);
}

StringTree RandomScheduler::print(const AtomExternalPort &port) {
  string ret = port.name();

  /*if (port.hasPortValue()) {
    string portStr = port.portValue().toString();

    if (portStr.size() > 0) {
      ret = ret + " (" + portStr + ")";
    }
    else {
      ret = ret + " (<no_value>)";
    }
  }*/

  return StringTree(ret);
}

StringTree RandomScheduler::print(const AtomExportPort &port) {
  StringTree ret(port.name());

  for (unsigned int i = 0 ; i < port.internalPorts().size() ; ++i) {
    const AtomInternalPort &internalPort = *(port.internalPorts()[i]);
    ret.addChild(print(internalPort));
  }

  return ret;
}

StringTree RandomScheduler::print(const InteractionValue &interaction) {
  ostringstream oss;

  oss << interaction;

  oss << " " << interaction.timingConstraint();
  oss << " " << interaction.timingConstraintAfterPriorities() << "*";

  return StringTree(oss.str());
}

StringTree RandomScheduler::print(const Connector &connector) {
  StringTree ret(connector.name());

  if (connector.hasExportedPort()) {
    StringTree portTree = print(connector.exportedPort());
    ret.addChild(portTree);
  }

  vector<InteractionValue *> interactions = connector.enabledInteractions();
  for (unsigned int i = 0 ; i < interactions.size() ; ++i) {
    StringTree interactionTree = print(*interactions[i]);
    ret.addChild(interactionTree);
  }
  connector.release(interactions);

  return ret;
}

StringTree RandomScheduler::print(const Atom &atom) {
  StringTree ret(atom.name());

  for (map<string, AtomExportPort *>::const_iterator portIt = atom.ports().begin() ;
       portIt != atom.ports().end() ;
       ++portIt) {
    const AtomExportPort &port = *(portIt->second);
    StringTree portTree = print(port);
    ret.addChild(portTree);
  }

  for (map<string, AtomInternalPort *>::const_iterator portIt = atom.internalPorts().begin() ;
       portIt != atom.internalPorts().end() ;
       ++portIt) {
    const AtomInternalPort &port = *(portIt->second);

    if (!port.isExported()) {
      StringTree portTree = print(port);
      ret.addChild(portTree);
    }
  }

  for (map<string, AtomExternalPort *>::const_iterator portIt = atom.externalPorts().begin() ;
       portIt != atom.externalPorts().end() ;
       ++portIt) {
    const AtomExternalPort &port = *(portIt->second);
    StringTree portTree = print(port);
    ret.addChild(portTree);
  }

  string atomStr = atom.toString();
  string::const_iterator beginIt = atomStr.begin();
  string::const_iterator strIt = atomStr.begin() ;

  while (strIt != atomStr.end()) {
    if (*strIt == '\n') {
      string childStr = string(beginIt, strIt);
      ret.addChild(childStr);
      beginIt = strIt + 1;
    }

    ++strIt;
  }

  if (beginIt != atomStr.end()) {
    string childStr = string(beginIt, strIt);
    ret.addChild(childStr);
  }

  return ret;
}

StringTree RandomScheduler::print(const Compound &compound) {
  StringTree ret(compound.name());

  for (map<string, CompoundExportPort *>::const_iterator portIt = compound.ports().begin() ;
       portIt != compound.ports().end() ;
       ++portIt) {
    const CompoundExportPort &port = *(portIt->second);
    StringTree portTree = print(port);
    ret.addChild(portTree);
  }

  for (map<string, Connector *>::const_iterator connIt = compound.connectors().begin() ;
       connIt != compound.connectors().end() ;
       ++connIt) {
    const Connector &connector = *(connIt->second);
    StringTree connectorTree = print(connector);
    ret.addChild(connectorTree);
  }

  for (map<string, Component *>::const_iterator connIt = compound.components().begin() ;
       connIt != compound.components().end() ;
       ++connIt) {
    const Component &component = *(connIt->second);
    StringTree componentTree = print(component);
    ret.addChild(componentTree);
  }

  return ret;
}

StringTree RandomScheduler::print(const Component &component) {
  if (component.type() == COMPOUND) {
    const Compound &compound = (const Compound &) component;
    return print(compound);
  }
  else if (component.type() == ATOM) {
    const Atom &atom = (const Atom &) component;
    return print(atom);
  }
  else {
    assert(false);
  }

  return StringTree();
}
