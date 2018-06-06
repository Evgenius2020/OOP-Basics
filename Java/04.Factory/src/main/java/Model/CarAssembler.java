package Model;

public class CarAssembler implements Runnable {
    private Store _bodyStore;
    private Store _engineStore;
    private Store _carStore;
    private int _productionTime;

    public CarAssembler(Store bodyStore, Store engineStore, Store carStore, int productionTime) {
        _bodyStore = bodyStore;
        _engineStore = engineStore;
        _productionTime = productionTime;
        _carStore = carStore;
    }

    public void run() {
        while (true) {
            Product body = _bodyStore.popProduct();
            System.out.println("Assembler: picked a Body with id#" + body.getId());
            Product engine = _engineStore.popProduct();
            System.out.println("Assembler: picked an Engine with id#" + engine.getId());

            try {
                Thread.sleep(_productionTime * 1000);
            } catch (Exception e) {
            }
            int carId = _carStore.getNextId();
            _carStore.pushProduct(new Product(carId, ProductType.Car));
            System.out.println("Assembler: created a Car with id#" + carId);
        }
    }
}