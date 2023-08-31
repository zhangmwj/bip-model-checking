
package ujf.verimag.bip.parser.error;

import ujf.verimag.bip.error.GenericError;

/**
 * Exception used by the Package Loader when an error is encountered
 */
public class PropertyException extends Exception {
    private static final long serialVersionUID = 1L;

    /**
     * Creates a new exception with the given error message
     * @param message the error message
     */
    public PropertyException(String message) {
        super(message);
    }

    /**
     * Creates a new exception and use the given throwable as the cause
     * @param cause the throwable that caused the error
     */
    public PropertyException(Throwable cause){
        super(cause);
    }
    
    /**
     * Creates a new exception with a given message and throwable cause
     * @param message the message
     * @param cause the cause
     */
    public PropertyException(String message,
            Throwable cause){
        super(message,cause);
    }
    
    /**
     * The array of errors that caused this exception
     */
    private GenericError[] errors;
    
    /**
     * Get the errors that caused this exception
     * @return the array of errors
     */
    public GenericError[] getErrors() {
        if (errors == null) errors = new GenericError[0];
        return errors;
    }

    /**
     * Creates an exception and attaches the error array as the cause.
     * @param errors the errors causing the exception.
     */
    public PropertyException(GenericError[] errors){
        this.errors = errors;
    }
}