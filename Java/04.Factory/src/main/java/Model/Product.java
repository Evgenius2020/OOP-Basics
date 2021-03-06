package Model;

public class Product {
    private int _id;
    private ProductType _type;

    public int getId() {
        return _id;
    }

    public ProductType getType() {
        return _type;
    }

    public Product(int id, ProductType type) {
        _id = id;
        _type = type;
    }

    @Override
    public String toString() {
        return String.format("%s#%d", _type, _id);
    }
}
