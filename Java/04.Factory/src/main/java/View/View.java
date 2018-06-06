package View;

import Model.Product;
import Model.ProductType;
import javafx.scene.layout.HBox;

public class View extends HBox {
    private ProductPane _accessoriesPane;
    private ProductPane _bodiesPane;
    private ProductPane _enginesPane;
    private ProductPane _carsPane;

    public View() {
        _accessoriesPane = new ProductPane(ProductType.Accessories);
        _bodiesPane = new ProductPane(ProductType.Body);
        _enginesPane = new ProductPane(ProductType.Engine);
        _carsPane = new ProductPane(ProductType.Car);

        this.getChildren().addAll(_accessoriesPane,_bodiesPane, _enginesPane, _carsPane);
    }

    public ProductPane getAccesoriesPane() {
        return _accessoriesPane;
    }

    public ProductPane getBodiesPane() {
        return _bodiesPane;
    }

    public ProductPane getEnginesPane() {
        return _enginesPane;
    }

    public ProductPane getCarsPane() {
        return  _carsPane;
    }
}