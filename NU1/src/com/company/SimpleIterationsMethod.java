package com.company;

// Не работает
// https://upload.wikimedia.org/wikipedia/ru/0/09/Xy.png

public class SimpleIterationsMethod extends Shared.MethodRunnable {
    public static void main(String[] args) {
        (new SimpleIterationsMethod()).run();
    }

    @Override
    public double calcResult() {
        double savedC = this.c;
        this.c = this.phi0(savedC);

        return this.c - savedC;
    }

    @Override
    public void onDataRequested() {
        double q = this.maxPhi(this.a, this.b);
        this.additionalCoef = (1 - q) / q;
        this.c = this.b > this.a ? this.b : this.a;
    }

    private double phi0(double x) {
        return (3 / (x * x - 1)); // Где взять?
    }

    private double phi1(double x) {
        return ((-6 * x) / Math.pow(x * x - 1, 2)); // Где взять?
    }

    private double maxPhi(double a, double b) {
        return Math.max(this.phi1(a), this.phi1(b));
    }
}
