import java.util.Random;

public class Main {

    public static void main(String[] args) {
        Simulation simulation = new Simulation();


        for(int i = 1; i <= simulation.getDuration(); i++) {
            simulation.setClock(i);

            if(simulation.isCustomerArrived()) {
                simulation.insertCustomer(i);
            }

            simulation.isStartCustomerService();
            //simulation.queue.display(); // queue debug
        }

        simulation.printStat();

    }

}

class Node {
    private Customer customer;
    private Node link;

    public Customer getCustomer() {
        return customer;
    }

    public Node getLink() {
        return link;
    }

    public void setCustomer(Customer customer) {
        this.customer = customer;
    }

    public void setLink(Node link) {
        this.link = link;
    }
}

class QueueType {
    private Node front;
    private Node rear;

    int queueSize = 0;

    public QueueType() {
        front = null;
        rear = null;
    }

    public Node getFront() {
        return front;
    }

    public Node getRear() {
        return rear;
    }

    public void setFront(Node front) {
        this.front = front;
    }

    public void setRear(Node rear) {
        this.rear = rear;
    }

    /* 큐가 비어 있는 지 검사 */
    public boolean isEmpty() {
        if (front == null)
            return true;
        return false;
    }

    /* 큐가 비어 있는 지 검사 + 비어 있을 경우 메세지 출력 */
    public boolean isEmpty(String msg) {
        if (front == null) {
            System.out.println(msg);
            return true;
        }
        return false;
    }

    /* 삽입 연산 */
    public void enQueue(Customer customer) {
        queueSize++;

        Node node = new Node();

        node.setCustomer(customer);
        node.setLink(null);
        if (getFront() == null)
            setFront(node);
        else
            getRear().setLink(node);

        setRear(node);
    }

    /* 삭제 연산 */
    public Customer deQueue() {
        queueSize--;

        Node node = getFront();
        setFront(getFront().getLink());

        return node.getCustomer();
    }

    /* 앞에 있는 요소 삭제하지 않고 반환 */
    public Customer peek() {
        return front.getCustomer();
    }

    /* 모든 Node 출력 */
    public void display() {
        if (queueSize < 1) {
            System.out.println("[, ]");
            return;
        }

        Node nodeTemp = this.front;

        System.out.print("[");
        for (int i = 0; i < queueSize; i++) {
            System.out.print(nodeTemp.getCustomer().getNumber() + ", ");
            nodeTemp = nodeTemp.getLink();
        }
        System.out.print("]\n");
    }

}

class Customer {
    private int arrivalTime; // 도착 시간
    private int serviceTime; // 서비스 시간
    private int number; // 고객 번호
    private int endTime; // 서비스 끝나는 시간

    public Customer(int arrivalTime, int serviceTime, int number) {
        this.arrivalTime = arrivalTime;
        this.serviceTime = serviceTime;
        this.number = number;
    }

    /* 서비스 종료 시간 */
    public int getEndTime() {
        return endTime;
    }

    public void setEndTime(int time) { //서비스 시작 한 시간과 서비스 받을 시간을 더하면 종료되는 시간이 나온다.
        endTime = time + serviceTime;
    }
    public int getArrivalTime() {
        return arrivalTime;
    }

    public int getNumber() {
        return number;
    }
}

class Simulation {
    private final int MAX_QUEUE_SIZE =100;

    QueueType queue = new QueueType();

    private int duration = 10; // 시뮬레이션 시간
    private double arrivalProb = 0.7; // 하나의 시간 동안 도착하는 평균 고객의 수
    private int maxServTime = 5; // 한 명의 고객을 처리하는 최대 서비스 시간
    private int clock; // 현재 시각

    private boolean State = false; // true --> 서비스중, false --> 서비스 받는 사람 없음

    private int customers = 0; // 전체 고객 수
    private int servedCustomers = 0; // 서비스 받은 고객의 수
    private int waitedTime = 0; // 고객이 기다린 시간

    public void setClock(int time) {
        clock = time;
    }

    public int getDuration() {
        return duration;
    }

    /* 랜덤한 숫자를 생성해 고객이 도착했는지 안했는지를 판단한다*/
    public boolean isCustomerArrived() {
        System.out.println("현재시간 = " + clock);

        /* 큐 최대값 넘으면 무조껀 false 리턴 */
        if(MAX_QUEUE_SIZE <= queue.queueSize)
            return false;
        //TODO
            return  new Random().nextDouble(1d) < arrivalProb;
        //return  new Random().nextDouble() < arrivalProb;
    }

    /* 서비스 받을 시간 랜덤으로 뽑아주는 함수*/
    public int getServiceTime() {
        return new Random().nextInt(maxServTime ) + 1;
    }

    /* 새로 도착한 고객을 대기열에 추가한다*/
    public void insertCustomer(int arrivalTime) {
        int ServiceTime = getServiceTime();

        Customer customer = new Customer(arrivalTime, ServiceTime, customers);
        queue.enQueue(customer);

        System.out.println("고객 " + customers++ + "이 " + arrivalTime + "분에 들어옵니다. 서비스 시간은 " + ServiceTime + "분 입니다.");
    }

    /* 서비스 받고 있는 손님이 서비스가 끝났는지 확인 하는 함수 */
    public boolean isEndService() {
        return clock >= queue.getFront().getCustomer().getEndTime();
    }

    /* 손님 서비스 시작 */
    public void isStartCustomerService() {

        /* 대기실에 없으면 리턴 */
        if(queue.isEmpty())
            return;

        /* 이미 서비스 받고 있으면 리턴 */
        if(!isEndService() && State)
            return;

        /* 서비스 상태 확인  */
        if(State) {
            removeCustomer();
            servedCustomers++;
            State = false;
        }

        /* 서비스 받고 뒤에 손님이 없으면 리턴 */
        if(queue.isEmpty())
            return;

        waitedTime  += clock - queue.getFront().getCustomer().getArrivalTime(); // 고객이 기다린 시간
        queue.getFront().getCustomer().setEndTime(clock);
        State = true;

        System.out.println("고객 " + queue.getFront().getCustomer().getNumber() + "이 " + clock+ "분에 서비스를 시작합니다. 대기시간은 " + (clock - queue.getFront().getCustomer().getArrivalTime()) + "분이었습니다.");
    }

    /* 손님 삭제  */
    public void removeCustomer() {
        queue.deQueue();
    }

    /* 통계치(앞서 시뮬레이션 결과)를 출력 함수 */
    public void printStat() {
        System.out.println("서비스 받은 고객의 수 = " + servedCustomers + "명");
        System.out.println("인당 평균 대기 시간 = " + Math.round( ((double) waitedTime / (double) servedCustomers ) * 1000000) / 1000000.000000 + "분"); // 6자리 이후 반올림
        System.out.println("아직 대기중인 고객의 수 = " + (customers - servedCustomers + "명"));
    }

}
