public class Controller {
    private GameModel _gameModel;

    public Controller(int fieldHeight, int fieldWidth, int usedColors) {
        _gameModel = new GameModel(fieldHeight, fieldWidth, usedColors);
    }

    public void down() {
        _gameModel.step();
    }

    public int[][] getField() {
        return _gameModel.getField();
    }

    public  GameModel getModel() {
        return _gameModel;
    }
}
