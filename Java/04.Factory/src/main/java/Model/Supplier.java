package Model;

public class Supplier implements Runnable {
    private Store _store;
    private int _timeForProduct;
    private ProductType _productType;

    public Supplier(Store store, int productionTime, ProductType productType) {
        _store = store;
        _timeForProduct = productionTime;
        _productType = productType;
    }

    public void run() {
        while(true) {
            int productId = _store.getNextId();
            try {
                Thread.sleep(_timeForProduct * 1000);
            }
            catch (Exception e) {
            }
            _store.pushProduct(new Product(productId, _productType));
            System.out.println("Model.Supplier: created a " + _productType.toString() + " with id#" + productId);
        }
    }
}