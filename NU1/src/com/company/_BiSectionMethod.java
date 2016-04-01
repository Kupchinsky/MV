package com.company;

// Сдал
public class _BiSectionMethod extends Shared.MethodRunnable {
    public static void main(String[] args) {
        (new _BiSectionMethod()).run();
    }

    private double fa, fc;

    @Override
    public double calcResult() {
        this.c = this.calcC();
        this.fa = Shared.func(this.a);
        this.fc = Shared.func(this.c);

        return this.fc;
    }

    @Override
    public void preCalc() {
        if (this.fa * this.fc < 0) {
            this.b = this.c;
        } else {
            this.a = this.c;
        }
    }

    private double calcC() {
        return (this.b + this.a) / 2;
    }
}
