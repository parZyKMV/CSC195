package YushanoBoken.Model;

import java.util.ArrayList;

public class Inventory {
    protected ArrayList<Item> inventory;
    private final int maxCapacity = 5;

    public Inventory() {
        inventory = new ArrayList<>();
    }

    public void addItem(Item item) {
        if (inventory.size() == maxCapacity) {
            System.out.println("You inventory is full");
        }else {
            inventory.add(item);
        }
    }
    public ArrayList<Item> getItems() {
        return inventory;
    }

    public boolean removeItem(Item item) {
        if (inventory.contains(item)) {
            inventory.remove(item);
            return true;
        }
        return false;
    }


    public Item getItem(Item type){
        for (Item item : inventory) {
            if (item.equals(type)) {
                return item;
            }
        }
        return null;
    }

}
