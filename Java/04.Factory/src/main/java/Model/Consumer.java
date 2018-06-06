package Model;

class Consumer implements Runnable{
    private Store _store;

    Consumer(Store store){
        _store = store;
    }

    public void run(){
        for (int i = 1; i < 6; i++) {
            Product product = _store.popProduct();
            System.out.println("Model.Consumer: received a product with id#" + product.getId());
        }
    }
}