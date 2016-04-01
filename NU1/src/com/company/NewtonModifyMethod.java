package com.company;

// Работает, сдать
// https://upload.wikimedia.org/wikipedia/ru/thumb/5/5c/Newton_mod.PNG/300px-Newton_mod.PNG

public class NewtonModifyMethod extends Shared.MethodRunnable {
    private double savedC, savedDerivative;

    public static void main(String[] args) {
        (new NewtonModifyMethod()).run();
    }

    @Override
    public double calcResult() {
        this.savedC = this.c;
        this.c = this.c - Shared.func(this.c) / this.savedDerivative;

        return this.savedC - this.c;
    }

    @Override
    public void onDataRequested() {
        //Выбор начального приближения
        this.c = Shared.func(this.a) * Shared.derivative(this.a) > 0 ? this.b : this.a;
        this.savedC = this.c;
        this.savedDerivative = Shared.derivative(this.c);
    }
}