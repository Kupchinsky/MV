package com.company;

/**
 * Created by killer on 05.04.2016.
 */
public class AllIn {
    public static void main(String[] args) {
        (new ChebyshevMethod()).run();
        (new NewtonModifyMethod()).run();
        (new NewtonMethod()).run();
    }
}
