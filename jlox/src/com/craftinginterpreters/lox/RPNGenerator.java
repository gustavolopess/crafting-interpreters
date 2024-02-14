package com.craftinginterpreters.lox;


// Visitor to turn an arithmetic operator into reverse polish notation
public class RPNGenerator implements Expr.Visitor<String> {
    String generate(Expr expr) {
        return expr.accept(this);
    }

    @Override
    public String visitBinaryExpr(Expr.Binary expr) {
        return this.toRNP(expr.operator.lexeme, expr.left, expr.right);
    }

    @Override
    public String visitUnaryExpr(Expr.Unary expr) {
        return this.toRNP(expr.operator.lexeme, expr.right);
    }

    @Override
    public String visitGroupingExpr(Expr.Grouping expr) {
        return this.toRNP(null, expr.expression);
    }

    @Override
    public String visitLiteralExpr(Expr.Literal expr) {
        if (expr.value == null) return "nil";
        return expr.value.toString();
    }

    private String toRNP(String operator, Expr... exprs) {
        StringBuilder builder = new StringBuilder();
        
        for (int i = 0; i < exprs.length; i++) {
            builder.append(exprs[i].accept(this));
            if (operator != null || i + 1 < exprs.length) {
                builder.append(" ");
            }
        }
       
        if (operator != null) {
            builder.append(operator);
        }
        
        return builder.toString();
    }

    public static void main(String[] args) {
        // (1 + 2) * (4 - 3) -> 1 2 + 4 3 - *
        Expr _1plus2 = new Expr.Binary(
            new Expr.Literal(1), new Token(TokenType.PLUS, "+", null, 1), new Expr.Literal(2)
        );
        Expr _4minus3 = new Expr.Binary(
            new Expr.Literal(4),new Token(TokenType.MINUS, "-", null, 1), new Expr.Literal(3)
        ); 
        Expr expr = new Expr.Binary(
            new Expr.Grouping(_1plus2), 
            new Token(TokenType.STAR, "*", null, 1), 
            new Expr.Grouping(_4minus3)
        );

        System.out.println(new RPNGenerator().generate(expr));

        // (2 + (1 + 2) + (4 - 3)) -> 2 1 2 + + 4 3 - +
        Expr expr2 = new Expr.Binary(
            new Expr.Literal(2), 
            new Token(TokenType.PLUS, "+", null, 1), 
            new Expr.Binary(
                new Expr.Grouping(_1plus2),
                new Token(TokenType.PLUS, "+", null, 1), 
                new Expr.Grouping(_4minus3)
            )
        );

        System.out.println(new RPNGenerator().generate(expr2));
    }
}
