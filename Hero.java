package YushanoBoken.Model;

import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class Hero extends Character{
    protected int mp;
    protected int maxHeroHp;
    protected int maxHeroMp;
    protected boolean isDisable;
    protected Inventory inventory;
    protected ArrayList<Magic> magic;
    private int experienceNeededToLevelUp;

    public Hero(HeroName heroName) {
        if (heroName == HeroName.GALAHAD) {
            setName("Galahad");
            setHp(20);
            setMaxHeroHp(20);
            setAttack(6);
            setDefense(6);
            setExperienceNeededToLevelUp(15);
        } else if (heroName == HeroName.BALIN) {
            setName("Balin");
            setHp(15);
            setMaxHeroHp(15);
            setAttack(7);
            setDefense(7);
            setExperienceNeededToLevelUp(20);
        } else if (heroName == HeroName.ELAINE) {
            setName("Elaine");
            setHp(25);
            setMaxHeroHp(25);
            setAttack(5);
            setDefense(5);
            setExperienceNeededToLevelUp(10);
        }
        setLevel(1);
        setExp(0);
        setMp(20);
        setMaxHeroMp(20);
        inventory = new Inventory();
        magic = new ArrayList<>();
    }

    public int getMaxHeroHp() {
        return maxHeroHp;
    }

    public void setMaxHeroHp(int maxHeroHp) {
        this.maxHeroHp = maxHeroHp;
    }

    public boolean isDisable() {
        return isDisable;
    }

    public void setDisable(boolean disable) {
        isDisable = disable;
    }

    public int getExperienceNeededToLevelUp() {
        return experienceNeededToLevelUp;
    }

    public void setExperienceNeededToLevelUp(int experienceNeededToLevelUp) {
        this.experienceNeededToLevelUp = experienceNeededToLevelUp;
    }

    public void levelUp(int exp) {
        setExp(getExp() + exp);
        if (getExp() >= getExperienceNeededToLevelUp()){
            setLevel(getLevel() + 1);
            setHp(getHp() + 2);
            setMaxHeroHp(getMaxHeroHp() + 2);
            setMp(getMp() + 1);
            setMaxHeroMp(getMaxHeroMp() + 1);
            setAttack(getAttack() + 1);
            setDefense(getDefense() + 1);
            setExp(0);
            setExperienceNeededToLevelUp(getExperienceNeededToLevelUp() + 1);
            learnANewMagic();
        }
    }

    public Inventory getInventory() {
        return inventory;
    }

    public void useItem(Item item) {
        Item items = inventory.getItem(item);
        if (items != null) {
            boolean use = items.useItem(this);
            if (use == true) {
                inventory.removeItem(item);
            }
        }
    }

    public void addItem(Item item) {
        inventory.addItem(item);
    }

    public boolean displayInventory() {
        if (!inventory.inventory.isEmpty()) {
            int index = 1;
            for (Item item : inventory.inventory) {
                System.out.println(index + ". " + item.getType());
                index++;
            }
            return true;
        }
        return false;
    }

    private void learnANewMagic(){
        if (magic.size() >= 6){
            return;
        }
        Magic newMagic = null;
        if (getLevel() == 2){
            MagicType[] basic = {MagicType.Fire, MagicType.Blizzard, MagicType.Thunder};
            newMagic = new Magic(basic[new Random().nextInt(basic.length)]);
        }else if (getLevel() % 10 == 0 && getLevel() <= 53){
            MagicType[] advanced = {MagicType.Aero, MagicType.Stop, MagicType.Cure, MagicType.Blizzard, MagicType.Thunder,MagicType.Fire};
            for (MagicType type : advanced){
                if (!hasMagic(type)){
                    newMagic = new Magic(type);
                    break;
                }
            }
        }
        if (newMagic != null){
            if (magic.size() < 4){
                magic.add(newMagic);
                System.out.println("You just learned " + newMagic.getType());
            }else{
                replaceMagic(newMagic);
            }
        }
    }

    private boolean hasMagic(MagicType type){
        for (Magic m : magic){
            if (m.getType() == type){
                return true;
            }
        }
        return false;
    }

    private void replaceMagic(Magic newMagic){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Your hero already has 4 magics. Do you want to replace one? (Yes/No)");
        String answer = scanner.nextLine().trim().toLowerCase();

        if (answer.equals("yes")) {
            System.out.println("Choose the magic to replace:");
            for (int i = 0; i < magic.size(); i++) {
                System.out.println((i + 1) + ". " + magic.get(i).getType());
            }
            int option = scanner.nextInt() - 1;

            if (option >= 0 && option < magic.size()) {
                System.out.println("You have replaced " + magic.get(option).getType() + " for " + newMagic.getType());
                magic.set(option, newMagic);
            } else {
                System.out.println("Invalid option. The new magic was not learned.");
            }
        } else {
            System.out.println(getName() + " has decided not to learn " + newMagic.getType());
        }
    }

    public boolean displayMagic(){
        if (!magic.isEmpty()){
            int index = 1;
            for (Magic m : magic){
                System.out.println(index + ". " + m.getType() + m.getStatusEffect());
                index++;
            }
            return true;
        }
        return false;
    }

    public ArrayList<Magic> getMagic() {
        return magic;
    }

    public int getMp() {
        return mp;
    }

    public void setMp(int mp) {
        this.mp = mp;
    }

    public int getMaxHeroMp() {
        return maxHeroMp;
    }

    public void setMaxHeroMp(int maxHeroMp) {
        this.maxHeroMp = maxHeroMp;
    }


}
