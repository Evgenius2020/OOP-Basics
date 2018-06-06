package Model;

import java.util.LinkedList;

public class Store {
    private LinkedList<Product> _products;
    private int _maximum;
    private int _nextId;

    public Store(int maximum) {
        _maximum = maximum;
        _nextId = 0;
        _products = new LinkedList<Product>();
    }

    public synchronized int getNextId() {
        return _nextId++;
    }

    public synchronized Product popProduct() {
        while (_products.size() == 0) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        Product product = _products.getFirst();
        _products.remove(product);
        notify();

        return product;
    }

    public synchronized void pushProduct(Product product) {
        while (_products.size() >= _maximum) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        _products.addFirst(product);
        notify();
    }
}