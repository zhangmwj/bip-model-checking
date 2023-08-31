package ujf.verimag.bip.parser.error;

import ujf.verimag.bip.error.GenericError;
import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.error.message.ErrorSeverity;

/**
 * Super class for error raised within the package loader.
 */
public class PropertyFileNotFoundError extends GenericError {

    /**
     * The faulty file name.
     */
    public final String fileName;
    
    public PropertyFileNotFoundError(String fileName) {
        super(-1, -1, ErrorCodeEnum.PropertyFileNotFound, ErrorSeverity.FATAL);
        this.fileName = fileName;
    }
    
}
