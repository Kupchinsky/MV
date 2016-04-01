package com.company;

// Сдал
public class _ChordMethod extends Shared.MethodRunnable {
    private double a, b;

    public static void main(String[] args) {
        (new _ChordMethod()).run();
    }

    @Override
    public double calcResult() {
        this.a = this.b - (this.b - this.a) * Shared.func(this.b) / (Shared.func(this.b) - Shared.func(this.a));
        this.b = this.a + (this.a - this.b) * Shared.func(this.a) / (Shared.func(this.a) - Shared.func(this.b));
        this.c = this.b;

        return this.b - this.a;
    }

    @Override
    public void onDataRequested() {
        this.a = super.a;
        this.b = super.b;
    }
}
