public class Controller {
    private GameModel _gameModel;

    public Controller(int fieldHeight, int fieldWidth, int usedColors) {
        _gameModel = new GameModel(fieldHeight, fieldWidth, usedColors);
    }

    public int[][] getField() {
        return _gameModel.getField();
    }

    public void down() {
        _gameModel.step();
    }

    public void left() {
        _gameModel.moveLeft();
    }

    public void right() {
        _gameModel.moveRight();
    }
}