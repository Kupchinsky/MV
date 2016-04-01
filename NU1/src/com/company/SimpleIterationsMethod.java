package com.company;

// Не работает
// https://upload.wikimedia.org/wikipedia/ru/0/09/Xy.png

public class SimpleIterationsMethod extends Shared.MethodRunnable {
    private double x1, x0;

    public static void main(String[] args) {
        (new SimpleIterationsMethod()).run();
    }

    @Override
    public double calcResult() {
        this.x0 = x1;
        this.x1 = Shared.func(this.x0);
        this.c = this.x1;

        return this.x0 - this.x1;
    }

    @Override
    public void preCalc() {
        this.x1 = b;
    }
}
