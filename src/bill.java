import java.util.ArrayList;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        ArrayList<Item> items = new ArrayList<Item>(
            Arrays.asList(
                new Item("りんご", 100, 10),
                new Item("バナナ", 80, 20),
                new Item("みかん", 50, 15),
                new Item("お肉", 500, 5),
                new Item("牛乳", 300, 25),
                new Item("魚", 400, 30)
            )
        );
        System.out.println("お会計システム作成");
    }
}

class Item {
    String name;
    int price;
    int stock;

    public Item(String name, int price, int stock) {
        this.name = name;
        this.price = price;
        this.stock = stock;
    }
}