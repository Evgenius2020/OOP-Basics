import java.awt.*;
import java.util.LinkedList;
import java.util.Random;

public class GameModel {
    private enum state {
        blockMoving, blockPlacing, rowProcessing, gameOver
    }

    private int[][] _field;
    private boolean[][][] _blockTemplates;
    private LinkedList<Point> _currentBlock;
    private int _nextBlockNumber;
    private int _nextColorNumber;
    private int _fieldWidth;
    private int _fieldHeight;
    private int _usedColors;
    private state _state;
    private int _score;

    public GameModel(int fieldHeight, int fieldWidth, int usedColors) {
        _fieldHeight = fieldHeight > 2 ? fieldHeight : 2;
        _fieldWidth = fieldWidth > 4 ? fieldWidth : 4;
        _field = new int[fieldHeight][fieldWidth];
        _usedColors = usedColors;
        _blockTemplates = initializeBlockTemplates();
        this.reset();
    }

    private boolean[][][] initializeBlockTemplates() {
        boolean[][][] blocks = new boolean[7][2][4];

        // -00-
        // -00-
        blocks[0] = new boolean[][]{{false, true, true, false}, {false, true, true, false}};

        // -00-
        // --00
        blocks[1] = new boolean[][]{{false, true, true, false}, {false, false, true, true}};

        // --00
        // -00-
        blocks[2] = new boolean[][]{{false, false, true, true}, {false,true, true, false}};

        // -000
        // -0--
        blocks[3] = new boolean[][]{{false, true, true, true}, {false, true, false, false}};

        // -000
        // ---0
        blocks[4] = new boolean[][]{{false, true, true, true}, {false, false, false, true}};

        // 0000
        // ----
        blocks[5] = new boolean[][]{{true, true, true, true}, {false, false, false, false}};

        // -000
        // --0-
        blocks[6] = new boolean[][]{{false, true, true, true}, {false, false, true, false}};

        return blocks;
    }

    public void reset() {
        _field = new int[_fieldHeight][_fieldWidth];
        for (int i = 0; i < _fieldHeight; i++) {
            for(int j = 0; j < _fieldWidth; j++) {
                _field[i][j] = -1;
            }
        }
        _currentBlock = null;
        _state = state.blockPlacing;
        _score = 0;
    }

    private void generateNextBlock() {
        Random rnd = new Random(System.currentTimeMillis());
        _nextBlockNumber = rnd.nextInt(7);
        _nextColorNumber = rnd.nextInt(_usedColors);
    }

    public void placeNextBlock(LinkedList<Point> block) {
        boolean[][] template = _blockTemplates[_nextBlockNumber];
        _currentBlock = new LinkedList<Point>();
        int rowCenter = (_fieldWidth - 4) / 2;

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                if (template[i][j]) {
                    if (_field[i][j + rowCenter] != -1) {
                        _state = state.gameOver;
                        return;
                    }
                    _field[i][j + rowCenter] = _nextColorNumber;
                    _currentBlock.add(new Point(j + rowCenter, i));
                }
            }
        }
        _state = state.blockMoving;
    }

    public void step() {
        switch (_state) {
            case gameOver: {
                return;
            }
            case blockPlacing: {
                generateNextBlock();
                placeNextBlock(_currentBlock);
                return;
            }
            case blockMoving: {
                if (!moveDown()) {
                    _state = state.rowProcessing;
                    _currentBlock = null;
                }
                return;
            }
            case rowProcessing: {
                for (int i = 0; i < _fieldHeight; i++) {
                    boolean isFullRow = true;
                    for (int j = 0; j < _fieldWidth; j++) {
                        if (_field[i][j] == -1) {
                            isFullRow = false;
                            break;
                        }
                    }
                    if (!isFullRow) {
                        continue;
                    }
                    _score += 1;
                    for (int k = i; k >= 0; k--) {
                        for (int j = 0; j < _fieldWidth; j++) {
                            _field[k][j] = (k != 0) ? _field[k-1][j] : -1;
                        }
                    }
                    return;
                }
                _state = state.blockPlacing;
            }
        }
    }

    public int[][] getNextBlock() {
        int[][] result = new int[4][4];

        boolean[][] template = _blockTemplates[_nextBlockNumber];
        for (int i = 0; i < 4; i++) {
            result[0][i] = -1;
            result[1][i] = template[0][i] ? _nextColorNumber : -1;
            result[2][i] = template[1][i] ? _nextColorNumber : -1;
            result[3][i] = -1;
        }
        return result;
    }

    public boolean moveBlock(int xShift, int yShift) {
        if (_currentBlock == null) {
            return false;
        }
        for(Point blockElement: _currentBlock) {
            if (!pointIsFree(blockElement.x + xShift, blockElement.y + yShift)) {
                return false;
            }
        }
        for(Point blockElement: _currentBlock) {
            _field[blockElement.y][blockElement.x] = -1;
        }
        for(Point blockElement: _currentBlock) {
            blockElement.x += xShift;
            blockElement.y += yShift;
            _field[blockElement.y][blockElement.x] = _nextColorNumber;
        }
        return true;
    }

    public boolean moveLeft() {
        return moveBlock(-1, 0);
    }

    public boolean moveRight() {
        return moveBlock(1, 0);
    }

    public boolean moveDown() {
        return moveBlock(0, 1);
    }

    private boolean pointIsFree(int x, int y) {
        if ((x < 0) || (x >= _fieldWidth)) {
            return false;
        }
        if ((y < 0) || (y >= _fieldHeight)) {
            return false;
        }

        if (_field[y][x] != -1) {
            for (Point neighbour : _currentBlock) {
                if ((neighbour.x == x) && (neighbour.y == y)) {
                    return true;
                }
            }
            return false;
        }

        return true;
    }

    public int[][] getField() {
        return _field;
    }

    public int getScore() {
        return _score;
    }
}