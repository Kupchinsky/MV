package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BiSectionMethod implements Runnable {
    double a, b, c;

    public static void main(String[] args) {
        (new BiSectionMethod()).run();
    }

    @Override
    public void run() {
        double epsilon = Math.pow(10, -5);

        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        try {
            System.out.print("a: ");
            this.a = Double.valueOf(bufferedReader.readLine());

            System.out.print("b: ");
            this.b = Double.valueOf(bufferedReader.readLine());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        int iterations = 0;
        CalcResult calcResult = this.calcResult();

        while (Math.abs(calcResult.fc) > epsilon) {
            iterations++;

            if (calcResult.fa * calcResult.fc < 0) {
                this.b = this.c;
            } else {
                this.a = this.c;
            }

            calcResult = this.calcResult();
        }

        System.out.println("Iterations = " + iterations + "; c = " + this.c);
    }

    CalcResult calcResult() {
        CalcResult calcResult = new CalcResult();

        this.c = this.calcC();

        calcResult.fa = this.func(this.a);
        calcResult.fb = this.func(this.b);
        calcResult.fc = this.func(this.c);

        return calcResult;
    }

    double calcC() {
        return (this.b + this.a) / 2;
    }

    double func(double x) {
        return (1 / Math.tan(x)) - (x / 5);
    }

    static class CalcResult {
        double fa, fb, fc;
    }
}
