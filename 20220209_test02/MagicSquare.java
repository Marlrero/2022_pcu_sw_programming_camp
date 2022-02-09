import java.util.Scanner;

public class MagicSquare {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.print("n by n? (n is odd number!) >> ");
        int mapSize = scan.nextInt();

        /* 홀수 마방진 이므로 짝수 일 경우 종료 */
        if(mapSize % 2 == 0)
            return;

        Map map = new Map(mapSize);

        for(int i = 1; i <= map.getSize() * map.getSize(); i++) {
            if(i == 1) {
                /* 1번 */
                map.setX(map.getSize() / 2);
                map.setY(map.getSize() - 1);;
                map.setMap(i);
            } else {
                if(!map.hasSpace()) { // 3번
                    /* 2번 */
                    map.setX(map.getX() + 1);
                    map.setY(map.getY() + 1);
                    map.setMap(i);
                } else {
                    /* 4번 */
                    map.setY(map.getY() - 1);
                    map.setMap(i);
                }
            }
        }

        /* 출력 */
        for(int y = 0; y < map.getSize(); y++) {
            for(int x = 0; x < map.getSize(); x++) {
                System.out.print(map.getSpace(x, y) + " ");
            }
            System.out.println();
        }

        scan.close();
    }

}

class Map {
    private int[][] map;
    private int size;
    private int x = 0, y = 0; //현재 좌표

    Map(int size) {
        this.size = size;
        map = new int[size][size];
    }

    int getSize() {
        return size;
    }

    void setMap(int value) {
        setX(checkMovingSpace(getX()));
        setY(checkMovingSpace(getY()));

        map[x][y] = value;
    }

    int getSpace(int x, int y) {
        return map[x][y];
    }

    /* 이동 할 공간에 이미 숫자가 있는지 확인 */
    boolean hasSpace() {
        int tempX = checkMovingSpace(x + 1), tempY = checkMovingSpace(y + 1); //임시 좌표를 만들어서 한 칸씩 이동시켜준다.

        if(map[tempX][tempY] == 0)
            return false;
        return true;
    }

    /* 정상적인 좌표 확인
    *  정상적인 좌표가 아니라면 정상적인 좌표로 변경 */
    int checkMovingSpace(int n) {
        if(size <= n)
            n -= size;

        if(n < 0)
            n += size;

        return n;
    }

    void setX(int x) {
        this.x = x;
    }

    void setY(int y) {
        this.y = y;
    }

    int getX(){
        return x;
    }

    int getY() {
        return y;
    }



}
