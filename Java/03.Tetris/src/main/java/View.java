import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

public class View extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        int _fieldHeight = 40;
        int _fieldWidth = 5;
        Controller controller = new Controller(_fieldHeight, _fieldWidth, 8);

        Pane view = new Pane();

        Pane gameField = new Pane();
        Rectangle _gameFieldSquares[][] = new Rectangle[_fieldHeight][_fieldWidth];
        for (int i = 0; i < _fieldHeight; i++) {
            for (int j = 0; j < _fieldWidth; j++) {
                Rectangle square = new Rectangle(15, 15);
                square.setArcHeight(3);
                square.setArcWidth(3);
                square.setX(15 * j);
                square.setY(15 * i);
                _gameFieldSquares[i][j] = square;
                gameField.getChildren().add(square);
            }
        }
        view.getChildren().add(gameField);

        primaryStage.setScene(new Scene(view, 500, 500));
        primaryStage.getScene().setOnKeyPressed((event) -> {
            if (event.getCode() == KeyCode.DOWN) {
                controller.down();
                for(int i = 0; i < _fieldHeight; i++) {
                    for(int j = 0; j < _fieldWidth; j++) {
                        _gameFieldSquares[i][j].setFill(getColorByCode(controller.getField()[i][j]));
                    }
                }
            }
        });
        primaryStage.show();
    }

    private Paint getColorByCode(int colorCode) {
        switch (colorCode) {
            case 0: return Color.VIOLET;
            case 1: return Color.BLUE;
            case 2: return Color.GREEN;
            case 3: return Color.RED;
            case 4: return Color.YELLOW;
            case 5: return Color.ORANGE;
            case 6: return Color.INDIGO;
            case 7: return Color.AQUA;
        }
        return  Color.BLACK;
    }
}