package com.company;

// Работает, сдать
//

public class ChebyshevMethod extends Shared.MethodRunnable {
    private double x0, fx0, fx0d1, fx0d2;

    public static void main(String[] args) {
        (new ChebyshevMethod()).run();
    }

    @Override
    public double calcResult() {
        this.x0 = this.c;
        this.fx0 = Shared.func(this.x0);
        this.fx0d1 = Shared.derivative(this.x0);
        this.fx0d2 = Shared.derivative2(this.x0);
        this.c = this.x0 - this.fx0 / this.fx0d1 - (this.fx0d2 * this.fx0 * this.fx0) / (2 * this.fx0d1 * this.fx0d1 * this.fx0d1);

        return this.x0 - this.c;
    }

    @Override
    public void onDataRequested() {
        this.c = this.a;
    }
}
