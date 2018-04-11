import javafx.animation.PauseTransition;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.util.Duration;

public class View extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        int fieldHeight = 20;
        int fieldWidth = 10;
        Controller controller = new Controller(fieldHeight, fieldWidth, 8);

        Pane gameField = new Pane();
        Rectangle gameFieldSquares[][] = new Rectangle[fieldHeight][fieldWidth];
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                Rectangle square = new Rectangle(30, 30);
                square.setArcHeight(3);
                square.setArcWidth(3);
                square.setX(30 * j);
                square.setY(30 * i);
                gameFieldSquares[i][j] = square;
                gameField.getChildren().add(square);
            }
        }

        Pane nextPart = new Pane();
        Rectangle nextPartSquares[][] = new Rectangle[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                Rectangle square = new Rectangle(10, 10);
                square.setX(10 * j);
                square.setY(10 * i);
                nextPartSquares[i][j] = square;
                nextPart.getChildren().add(square);
            }
        }

        Pane view = new Pane();
        view.getChildren().add(gameField);
        view.getChildren().add(nextPart);

        primaryStage.setScene(new Scene(view));
        primaryStage.setIconified(false);
        primaryStage.setTitle("Score: " + controller.getScore());

        PauseTransition nextStateTick = new PauseTransition();
        nextStateTick.setDuration(new Duration(300));
        nextStateTick.setOnFinished(event -> {
            nextState(primaryStage, fieldHeight, fieldWidth, controller, gameFieldSquares, nextPartSquares);
            nextStateTick.setDuration(new Duration(300));
            nextStateTick.play();
        });
        nextStateTick.play();

        primaryStage.getScene().setOnKeyPressed((event) -> {
            if (event.getCode() == KeyCode.LEFT) {
                controller.left();
                drawField(fieldHeight, fieldWidth, controller, gameFieldSquares);
            }
            if (event.getCode() == KeyCode.RIGHT) {
                controller.right();
                drawField(fieldHeight, fieldWidth, controller, gameFieldSquares);
            }
            if (event.getCode() == KeyCode.UP) {
                controller.rotate();
                drawField(fieldHeight, fieldWidth, controller, gameFieldSquares);
            }
            if (event.getCode() == KeyCode.DOWN) {
                nextState(primaryStage, fieldHeight, fieldWidth, controller, gameFieldSquares, nextPartSquares);
            }
        });
        primaryStage.show();
    }

    private void nextState(Stage primaryStage, int fieldHeight, int fieldWidth, Controller controller, Rectangle[][] gameFieldSquares, Rectangle[][] nextPartSquares) {
        controller.down();
        drawField(fieldHeight, fieldWidth, controller, gameFieldSquares);
        drawNextPart(controller.getNextPart(), nextPartSquares);
        primaryStage.setTitle("Score: " + controller.getScore());
    }

    private void drawNextPart(boolean[][] nextPart, Rectangle[][] nextPartSquares) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                nextPartSquares[i][j].setFill(nextPart[i][j] ? Color.GRAY : Color.TRANSPARENT);
            }
        }
    }

    private void drawField(int fieldHeight, int fieldWidth, Controller controller, Rectangle[][] gameFieldSquares) {
        for(int i = 0; i < fieldHeight; i++) {
            for(int j = 0; j < fieldWidth; j++) {
                gameFieldSquares[i][j].setFill(getColorByCode(controller.getField()[i][j]));
            }
        }
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
            case 7: return Color.DARKCYAN;
        }
        return  Color.BLACK;
    }
}