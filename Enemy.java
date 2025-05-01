package YushanoBoken.Model;

import java.util.Random;

public class Enemy extends Character {

    public Enemy(EnemyType enemyType){
        setLevel(1);
        if(enemyType == EnemyType.SLIME){
            setName("Slime");
            setHp(5);
            setAttack(3);
            setDefense(2);
            setExp(5);
        } else if (enemyType == EnemyType.SKELETON){
            setName("Skeleton");
            setHp(10);
            setAttack(5);
            setDefense(4);
            setExp(7);
        } else if (enemyType == EnemyType.GOBLIN){
            setName("Goblin");
            setHp(15);
            setAttack(6);
            setDefense(5);
            setExp(9);
        }
    }

    public Item dropLoot(){
        if (isDead() == true){
            ItemsType[] items = ItemsType.values();
            Random rand = new Random();
            int randomIndex = rand.nextInt(items.length);
            return new Item(items[randomIndex]);
        }
        return null;
    }

    public void levelUp(int level){
        setLevel(getLevel()+level);
        setHp(getHp()+level);
        setAttack(getAttack()+level);
        setDefense(getDefense()+level);
        setExp(getExp()+level);
    }
}
