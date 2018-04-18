class Producer implements Runnable {
    Store _store;

    Producer(Store store) {
        _store = store;
    }

    public void run() {
        for (int i = 1; i < 6; i++) {
            _store.pushProduct(new Product(i));
            System.out.println("Producer: created a product with id#" + i);
        }
    }
}