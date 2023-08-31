#!/usr/bin/awk -f 
## #############################################################
## Generates fischer n
## #############################################################
## writes files
##  fischer_XX
##  
##  where XX is a two-digit decimal for n
## #############################################################

function constants(OUT) {
  print "  const data int k = 2" > OUT;
  print "" > OUT;
}

function ports(OUT) {
  print "  port type port_tId (int id)" > OUT; 
  print "  port type port_t ()" > OUT; 
  print "  port type port_tPid (int pid, int id)" > OUT;
  print "" > OUT;
}

function atoms(OUT) {
  print "  atom type Atom(int param)\n" > OUT;
  print "    data int id = 0" > OUT;
  print "    data int pid = param\n" > OUT;
  print "    export port port_tId loop (id)" > OUT;
  print "    port port_t p1 ()" > OUT;
  print "    export port port_tPid p2 (pid, id)" > OUT;
  print "    port port_t p3 ()" > OUT;
  print "    port port_t p4 ()" > OUT;
  print "    export port port_tId p5 (id)\n" > OUT;
  print "    clock x\n" > OUT;
  print "    place A, req, wait, cs\n" > OUT;
  print "    initial to A\n" > OUT;
  print "    on loop from A to A" > OUT;
  print "    on loop from req to req" > OUT;
  print "    on loop from wait to wait" > OUT;
  print "    on loop from cs to cs\n" > OUT;
  print "    on p1 from A to req provided (id == 0) do {x = 0;}" > OUT;
  print "    on p2 from req to wait provided (x <= k) do {x = 0;}" > OUT;
  print "    on p3 from wait to req provided (id == 0) do {x = 0;}" > OUT;
  print "    on p4 from wait to cs provided (x > k && id == pid)" > OUT;
  print "    on p5 from cs to A\n" > OUT;
  print "    invariant atReq at req provided (x <= k)\n" > OUT;
  print "  end\n" > OUT;
}

function connectors(i, OUT) {
  PARAM = "port_tPid p";
  for(v = 1; v < i; v++){
    PARAM = PARAM ", port_tId p" v;
  }
  print "  connector type connectorP2(" PARAM ")" > OUT;
  DEFINE = "p";
  for(v = 1; v < i; v++){
    DEFINE = DEFINE " p" v;
  }
  print "    define " DEFINE > OUT;
  ACTION = "p.id = p.pid;";
  for(v = 1; v < i; v++){
    ACTION = ACTION " p" v ".id = p.pid;";
  }
  print "    on " DEFINE " down {" ACTION "}" > OUT;
  print "  end\n" > OUT;
  

  PARAM = "port_tId p1";
  for(v = 2; v <= i; v++){
    PARAM = PARAM ", port_tId p" v;
  }
  print "  connector type connectorP5(" PARAM ")" > OUT;
  DEFINE = "p1";
  for(v = 2; v <= i; v++){
    DEFINE = DEFINE " p" v;
  }
  print "    define " DEFINE > OUT;
  ACTION = "p1.id = 0;";
  for(v = 2; v <= i; v++){
    ACTION = ACTION " p" v ".id = 0;";
  }
  print "    on " DEFINE " down {" ACTION "}" > OUT;
  print "  end\n" > OUT;
}

function compound(i, OUT) {
  print "  compound type Compound()" > OUT;
  COMPONENT = "a1(1)";
  for (v = 2; v <= i; v++) {
    COMPONENT = COMPONENT ", a" v "(" v ")";
  }
  print "    component Atom " COMPONENT > OUT;

  for (v = 1; v <= i; v++) {
    PARAM = "a" v ".p2";
    for (u = 1; u <= i; u++) {
      if (u != v) {
        PARAM = PARAM ", a" u ".loop";
      }
    }
    print "    connector connectorP2 connectP2" v "(" PARAM ")" > OUT;

    PARAM = "a" v ".p5";
    for (u = 1; u <= i; u++) {
      if (u != v) {
        PARAM = PARAM ", a" u ".loop";
      }
    }
    print "    connector connectorP5 connectP5" v "(" PARAM ")" > OUT;
  }
  print "  end\n" > OUT;
}

BEGIN {
  if(ARGC!=2) {
    print "wrong number of arguments" | "cat 1>&2";
    exit(1);
  }
 N = ARGV[1] + 0;

 print "** " N    ;
  if(N<=0) {
    print "*** non valid `N' (use option -vN=# )" | "cat 1>&2"
    exit 1
  }
#  printf "%02d\n", N;
## -- set output name ------------------------------------------
  if( N >= 10 ) { 
      NAME = "fischer_" N; }
  else {
      NAME = "fischer_0" N; }
  OUTPUT=(NAME ".bip");  
## -- generate ---------------------------------------------------------
  print "package " NAME "\n" > OUTPUT;
  constants(OUTPUT);
  ports(OUTPUT);
  atoms(OUTPUT);
  connectors(N, OUTPUT);
  compound(N, OUTPUT);
  print "end" > OUTPUT;

## -------------------------------------------------------------------------
  close(OUTPUT);
}
