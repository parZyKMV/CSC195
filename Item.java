package YushanoBoken.Model;

public class Item{
    private ItemsType type;
    private String description;
    private int effectOfItem;

    public Item(ItemsType type) {
        this.type = type;
        if (type == ItemsType.POTION){
            this.effectOfItem = 10;
            this.description= "Health 10 points of your Hp";
        } else if (type == ItemsType.ATTACK_STONE){
            this.effectOfItem = 1;
            this.description= "Increase your Attack Stat plus 1";
        } else if (type == ItemsType.DEFENSE_STONE){
            this.effectOfItem = 2;
            this.description= "Increase your Defense Stat plus 2";
        } else if (type == ItemsType.ETHER){
            this.effectOfItem = 5;
            this.description= "Restore your MP by 5";
        }
    }

    public ItemsType getType() {
        return type;
    }

    public boolean useItem(Hero hero){
        if(type.equals(ItemsType.POTION)){
            if (hero.hp >= hero.getMaxHeroHp()){
                System.out.println("You can't use it right now");
                return false;
            } else if (hero.hp <= hero.getMaxHeroHp()) {
                hero.setHp(hero.getHp() + effectOfItem);
                if(hero.hp > hero.getMaxHeroHp()){
                    hero.setHp(hero.getMaxHeroHp());
                }
                System.out.println("You have been healed");
                return true;
            }
        } else if (type.equals(ItemsType.ATTACK_STONE)){
            if(hero.attack == 100){
                System.out.println("You can no longer increase your attack ");
                return false;
            }else{
                hero.setAttack(hero.getAttack() + effectOfItem);
                System.out.println("You attack have been increased");
                return true;
            }
        } else if (type.equals(ItemsType.DEFENSE_STONE)) {
            if(hero.defense == 100){
                System.out.println("You can no longer increase your defense ");
                return false;
            }else {
                hero.setDefense(hero.getDefense() + effectOfItem);
                System.out.println("You defense have been increased");
                return true;
            }
        }else if(type.equals(ItemsType.ETHER)){
            if (hero.mp >= hero.getMaxHeroMp()){
                System.out.println("You can't use it right now");
                return false;
            }else if (hero.mp <= hero.getMaxHeroMp()) {
                hero.setMp(hero.getMp() + effectOfItem);
                if(hero.mp > hero.getMaxHeroMp()){
                    hero.setMp(hero.getMaxHeroMp());
                }
                System.out.println("You MP have been restored");
                return true;
            }

        }
        return false;
    }

    public String toString(){
        return type + " " + description;
    }

}