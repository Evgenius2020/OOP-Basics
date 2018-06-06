package View;

import Model.Product;
import Model.ProductType;
import javafx.scene.control.ListView;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

class ProductPane extends VBox {
    private ProductType _type;
    private ListView<Product> _listView;
    private Text _text;

    public ProductPane(ProductType type) {
        _type = type;
        _listView =  new ListView<>();
        _text = new Text();
        this.getChildren().addAll(_text, _listView);
    }

    public ProductType getType() {
        return _type;
    }

    public ListView<Product> getListView() {
        return _listView;
    }

    public Text getText() {
        return _text;
    }
}
