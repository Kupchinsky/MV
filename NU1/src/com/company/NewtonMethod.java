package com.company;

// Работает, сдать
// Метод касательных, https://upload.wikimedia.org/wikipedia/commons/thumb/8/8c/Newton_iteration.svg/800px-Newton_iteration.svg.png

public class NewtonMethod extends Shared.MethodRunnable {
    private double savedC;

    public static void main(String[] args) {
        (new NewtonMethod()).run();
    }

    @Override
    public double calcResult() {
        this.savedC = this.c;
        this.c = this.c - Shared.func(this.c) / Shared.derivative(this.c);

        return this.savedC - this.c;
    }

    @Override
    public void onDataRequested() {
        //Выбор начального приближения
        this.c = Shared.func(this.a) * Shared.derivative2(this.a) > 0 ? this.a : this.b;
        this.savedC = this.c;
    }
}
