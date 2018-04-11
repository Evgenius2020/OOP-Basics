import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

public class GameModel {
    private enum state {
        blockMoving, blockPlacing, rowProcessing, gameOver
    }

    private int[][] _field;
    private ArrayList<boolean[][]> _blockTemplates;
    private ArrayList<Point> _currentBlock;
    private int _currentBlockNumber;
    private int _currentColorNumber;
    private int _nextBlockNumber;
    private int _currentBlockStartX;
    private int _currentBlockStartY;
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

    private boolean[][] generateTemplateByString(String str) {
        boolean[][] result = new boolean[4][4];
        for (int i = 0; i < 16; i++) {
            result[i/4][i%4] = str.charAt(i) == '0';
        }
        return result;
    }
    private ArrayList<boolean[][]> initializeBlockTemplates() {
        ArrayList<boolean[][]> result = new ArrayList<>();

        // -00-
        // -00-
        // ----
        // ----
        result.add(generateTemplateByString("-00--00---------"));
        result.add(generateTemplateByString("-00--00---------"));
        result.add(generateTemplateByString("-00--00---------"));
        result.add(generateTemplateByString("-00--00---------"));

        // -00- --0-
        // --00 -00-
        // ---- -0--
        // ---- ----
        result.add(generateTemplateByString("-00---00--------"));
        result.add(generateTemplateByString("--0--00--0------"));
        result.add(generateTemplateByString("-00---00--------"));
        result.add(generateTemplateByString("--0--00--0------"));

        // --00 -0--
        // -00- -00-
        // ---- --0-
        // ---- ----
        result.add(generateTemplateByString("--00-00---------"));
        result.add(generateTemplateByString("-0---00---0-----"));
        result.add(generateTemplateByString("--00-00---------"));
        result.add(generateTemplateByString("-0---00---0-----"));

        // -000 -0-- ---0 -00-
        // -0-- -0-- -000 --0-
        // ---- -00- ---- --0-
        // ---- ---- ---- ----
        result.add(generateTemplateByString("-000-0----------"));
        result.add(generateTemplateByString("-0---0---00-----"));
        result.add(generateTemplateByString("---0-000--------"));
        result.add(generateTemplateByString("-00---0---0-----"));

        // 000- --0- 0--- -00-
        // --0- --0- 000- -0--
        // ---- -00- ---- -0--
        // ---- ---- ---- ----
        result.add(generateTemplateByString("000---0---------"));
        result.add(generateTemplateByString("--0---0--00-----"));
        result.add(generateTemplateByString("0---000---------"));
        result.add(generateTemplateByString("-00--0---0------"));

        // 0000 -0--
        // ---- -0--
        // ---- -0--
        // ---- -0--
        result.add(generateTemplateByString("0000------------"));
        result.add(generateTemplateByString("-0---0---0---0--"));
        result.add(generateTemplateByString("0000------------"));
        result.add(generateTemplateByString("-0---0---0---0--"));

        // 000- -0-- -0-- --0-
        // -0-- -00- 000- -00-
        // ---- -0-- ---- --0-
        // ---- ---- ---- ----
        result.add(generateTemplateByString("000--0----------"));
        result.add(generateTemplateByString("-0---00--0------"));
        result.add(generateTemplateByString("-0--000---------"));
        result.add(generateTemplateByString("--0--00---0-----"));

        return result;
    }

    public void reset() {
        _field = new int[_fieldHeight][_fieldWidth];
        for (int i = 0; i < _fieldHeight; i++) {
            for(int j = 0; j < _fieldWidth; j++) {
                _field[i][j] = -1;
            }
        }
        Random rnd = new Random(System.currentTimeMillis());
        _nextBlockNumber = rnd.nextInt(_blockTemplates.size());
        _currentBlock = null;
        _state = state.blockPlacing;
        _score = 0;
    }

    private void generateNextBlock() {
        Random rnd = new Random(System.currentTimeMillis());
        _currentBlockNumber = _nextBlockNumber;
        _nextBlockNumber = rnd.nextInt(_blockTemplates.size());
        _currentColorNumber = rnd.nextInt(_usedColors);
        _currentBlockStartX = (_fieldWidth - 4) / 2;
        _currentBlockStartY = 0;
        _currentBlock = generateBlockByTemplate
                (_blockTemplates.get(_currentBlockNumber), _currentBlockStartX, _currentBlockStartY);
    }

    public void step() {
        switch (_state) {
            case gameOver: {
                return;
            }
            case blockPlacing: {
                generateNextBlock();
                if (placeForBlockIsAvailable(_currentBlock, false)) {
                    placeCurrentBlock();
                    _state = state.blockMoving;
                }
                else {
                    _state = state.gameOver;
                }
                return;
            }
            case blockMoving: {
                if (!moveCurrentBlock(0, 1)) {
                    _state = state.rowProcessing;
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

    private boolean rotateCurrentBlock() {
        if ((_currentBlock == null) || (_state != state.blockMoving)) {
            return false;
        }
        int rotatedBlockNumber = (_currentBlockNumber / 4) * 4 + (_currentBlockNumber + 1) % 4;
        boolean[][] rotatedTemplate = _blockTemplates.get(rotatedBlockNumber);
        ArrayList<Point> nextState = generateBlockByTemplate(rotatedTemplate, _currentBlockStartX, _currentBlockStartY);
        if (!placeForBlockIsAvailable(nextState, true)) {
            return false;
        }
        deleteCurrentBlock();
        _currentBlock = nextState;
        _currentBlockNumber = rotatedBlockNumber;
        placeCurrentBlock();

        return true;
    }

    private boolean moveCurrentBlock(int xShift, int yShift) {
        if ((_currentBlock == null) || (_state != state.blockMoving)) {
            return false;
        }
        boolean[][] template = _blockTemplates.get(_currentBlockNumber);
        int templateStartX = _currentBlockStartX + xShift;
        int templateStartY = _currentBlockStartY + yShift;
        ArrayList<Point> nextState = generateBlockByTemplate(template, templateStartX, templateStartY);
        if (!placeForBlockIsAvailable(nextState,true)) {
            return false;
        }
        deleteCurrentBlock();
        _currentBlock = nextState;
        _currentBlockStartX += xShift;
        _currentBlockStartY += yShift;
        placeCurrentBlock();

        return true;
    }

    private void deleteCurrentBlock() {
        for(Point blockElement : _currentBlock) {
            _field[blockElement.y][blockElement.x] = -1;
        }
    }

    private void placeCurrentBlock() {
        for(Point blockElement : _currentBlock) {
            _field[blockElement.y][blockElement.x] = _currentColorNumber;
        }
    }

    private ArrayList<Point> generateBlockByTemplate(boolean[][] template, int xStartPos, int yStartPos) {
        ArrayList<Point> block = new ArrayList<>();

        for(int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if(template[i][j]) {
                    block.add(new Point(xStartPos + j, yStartPos + i));
                }
            }
        }

        return block;
    }

    private boolean placeForBlockIsAvailable(ArrayList<Point> block, boolean isBlockMovingMode) {
        for(Point blockElement: block){
            int x = blockElement.x;
            int y = blockElement.y;

            if ((x < 0) || (x >= _fieldWidth)) {
                return false;
            }
            if ((y < 0) || (y >= _fieldHeight)) {
                return false;
            }

            if (_field[y][x] != -1) {
                if (!isBlockMovingMode) {
                    return false;
                }
                boolean isElementOfBlock = false;
                for (Point neighbour : _currentBlock) {
                    if ((neighbour.x == x) && (neighbour.y == y)) {
                        isElementOfBlock = true;
                    }
                }
                if (!isElementOfBlock) {
                    return false;
                }
            }
        }
        return true;
    }

    public void moveLeft() {
        moveCurrentBlock(-1, 0);
    }

    public void moveRight() {
        moveCurrentBlock(1, 0);
    }

    public void rotate() {
        rotateCurrentBlock();
    }

    public int[][] getField() {
        return _field;
    }

    public boolean[][] getNextPart() {
        return _blockTemplates.get(_nextBlockNumber);
    }

    public int getScore() {
        return _score;
    }
}