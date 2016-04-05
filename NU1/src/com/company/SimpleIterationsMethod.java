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

        if (q > 1 || q < 0) {
            throw new RuntimeException("q is invalid");
        }

        this.additionalCoef = (1 - q) / q;
        this.c = Math.max(this.b, this.a);
    }

    private double phi0(double x) {
        return Shared.arcctg(x / 5);
    }

    private double phi1(double x) {
        return -5 / ((x * x) + 25);
    }

    private double maxPhi(double a, double b) {
        return Math.max(this.phi1(a), this.phi1(b));
    }
}
