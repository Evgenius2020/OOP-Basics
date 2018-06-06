package Model;

public class ThreadsApp {
    public static void main(String[] args) {
        Store engineStore = new Store(3);
        Store bodyStore = new Store(10);
        Store carStore = new Store(5);
        Supplier engineSupplier = new Supplier(engineStore, 1, ProductType.Engine);
        Supplier bodySupplier = new Supplier(bodyStore, 7, ProductType.Body);
        CarAssembler carAssembler = new CarAssembler(bodyStore, engineStore, carStore, 10);
        new Thread(engineSupplier).start();
        new Thread(bodySupplier).start();
        new Thread(bodySupplier).start();
        new Thread(bodySupplier).start();
        new Thread(carAssembler).start();
    }
}