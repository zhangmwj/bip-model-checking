package ujf.verimag.bip.parser.error;

import org.antlr.runtime.tree.CommonTree;
import org.antlr.runtime.tree.TreeNodeStream;

import ujf.verimag.bip.error.message.ErrorCodeEnum;
import ujf.verimag.bip.metamodel.AnnotatedEObject;

public class DuplicatedPropertyException extends Bip2WalkerException {

    private static final long serialVersionUID = 6958551503991300457L;
    
    /**
     * The model object found guilty of redefinition
     */
    protected AnnotatedEObject previousDeclaration;
    
    /**
     * The symbol redefined
     */
    protected String symbol;
    
    /**
     * Get the redefined symbol name
     * @return the redefined symbol name
     */
    public String getSymbol() {
        return symbol;
    }
    
    /**
     * Get the previous declaration
     * @return the previous declaration
     */
    public AnnotatedEObject getPreviousDeclaration() {
        return previousDeclaration;
    }

    public DuplicatedPropertyException(TreeNodeStream input, CommonTree start, AnnotatedEObject previous, String symbol) {
        super(input, start, ErrorCodeEnum.DuplicatedProperty);
        this.previousDeclaration = previous;
        this.symbol = symbol;
    }

}
