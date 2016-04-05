package com.company;

import javafx.util.Pair;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Shared {
    public static double func(double x) {
        return (1 / Math.tan(x)) - (x / 5);
    }

    private static double csc(double theta) {
        return 1.0 / Math.sin(theta);
    }

    private static double cot(double theta) {
        return 1.0 / Math.tan(theta);
    }

    public static double derivative(double x) {
        return -Math.pow(Shared.csc(x), 2) - 1;
    }

    public static double derivative2(double x) {
        return 2 * Shared.cot(x) * Math.pow(Shared.csc(x), 2);
    }

    public static double epsilon = Math.pow(10, -5);

    public static Pair<Double, Double> requestData() {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        double a, b;

        try {
            System.out.print("a: ");
            a = Double.valueOf(bufferedReader.readLine());

            System.out.print("b: ");
            b = Double.valueOf(bufferedReader.readLine());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        return new Pair<>(a, b);
    }

    public static abstract class MethodRunnable {
        protected double a, b, c, additionalCoef = 1;

        public final void run() {
            System.out.println("f(x) = ctg(x) - (x / 5)");
            System.out.println("epsilon: " + Shared.epsilon);
            System.out.println("method: " + this.getClass().getSimpleName());

            Pair<Double, Double> data = Shared.requestData();
            this.a = data.getKey();
            this.b = data.getValue();

            this.onDataRequested();

            int iterations = 1;
            double calcResult = this.calcResult();

            while (Math.abs(calcResult) > this.additionalCoef * Shared.epsilon) {
                iterations++;
                this.preCalc();
                calcResult = this.calcResult();
            }

            System.out.println("Iterations = " + iterations + "; c = " + this.c);
        }

        public abstract double calcResult();

        public void preCalc() {
        }

        public void onDataRequested() {
        }
    }
}
