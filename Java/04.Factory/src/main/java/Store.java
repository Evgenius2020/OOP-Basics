import java.util.LinkedList;

class Store {
    private LinkedList<Product> _products;

    public Store() {
        _products = new LinkedList<Product>();
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
        while (_products.size() >= 3) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        _products.addFirst(product);
        notify();
    }
}