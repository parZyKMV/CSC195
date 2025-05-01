package YushanoBoken.Model;
import java.util.Random;

public abstract class Character implements Attack, RecieveDamage, isDead {
    protected String name;
    protected int hp;
    protected int attack;
    protected int defense;
    protected int level;
    protected int exp;
    private boolean isDisable;
    private int damageAfterDefense;
    private StatusEffect effect;
    private int durationOfEffect = 1;
    private String effectDisplay;

    public int Attack(){
        return attack;
    }

    public void recieveDamage(int damage){
        if(damage <= 0)return;
        int defenseFactor = 2;
        int reduceDefense = this.defense/defenseFactor;
        int damageAfterDefense = Math.max(1, damage - reduceDefense);
        this.damageAfterDefense = damageAfterDefense;
        setHp(Math.max(0, this.hp - damageAfterDefense));
    }

    public boolean isDead(){
        return hp <= 0;
    }

    public void setEffect(StatusEffect effect){
        this.effect = effect;
        this.durationOfEffect = 1;
        switch(effect){
            case Burn:
                System.out.println(name + " has been burned. It will take damage for 3 turns.");
                this.effectDisplay = "\uD83D\uDD25";
                break;
            case Freeze:
                System.out.println(name + " has been frozen. It will not be able to move for 2 turns.");
                this.effectDisplay = "❄\uFE0F";
                isDisable = true;
                break;
            case Paralysis:
                System.out.println(name + " has been paralyzed. It may lose turns for 3 turns.");
                this.effectDisplay = "⚡";
                break;
            case Shield:
                System.out.println(name + " has activated a shield. He will take half damage for 5 turns.");
                this.effectDisplay = "\uD83C\uDF2A\uFE0F";
                break;
            case Stop:
                System.out.println(name + " has been stopped. You will lose 3 turns in a row.");
                this.effectDisplay = "⌛";
                isDisable = true;
                break;
            case Heal:
                setHp(this.hp + 8);
                System.out.println(name + " has been healed for 8 health points.");
                break;
            case RADIATION:
                System.out.println(name + " has been radiated and gonna lose 8 health points.");
                break;
        }
    }

    public void applyStatusEffect() {
        if (effect == null) return;
        switch (effect) {
            case Burn:
                if (durationOfEffect <= 3) {
                    setHp(this.hp - 1);
                }else {
                    this.effectDisplay = null;
                }
                break;
            case Freeze:
                if (durationOfEffect <= 2) {
                    isDisable = true;
                    System.out.println(name + " is frozen and cannot move.");
                } else {
                    isDisable = false;
                    System.out.println(name + " has thawed.");
                    this.effectDisplay = null;
                }
                break;
            case Paralysis:
                if (durationOfEffect <= 3) {
                    Random rand = new Random();
                    if (rand.nextInt(100) < 50) {
                        isDisable = true;
                        System.out.println(name + " is paralyzed and cannot move.");
                    } else {
                        isDisable = false;
                        this.effectDisplay = null;
                    }
                }
                break;
            case Shield:
                if (durationOfEffect <= 5) {
                    System.out.println(name + " is protected. Takes half damage.");
                } else {
                    System.out.println(name + " is no longer protected.");
                    effect = null;
                    this.effectDisplay = null;
                }
                break;
            case Stop:
                if (durationOfEffect <= 3) {
                    isDisable = true;
                    System.out.println(name + " is affected by Stop and loses this turn.");
                } else {
                    isDisable = false;
                    System.out.println(name + " has been released from the Stop effect.");
                    effect = null;
                    this.effectDisplay = null;
                }
                break;
            case RADIATION:
                if (durationOfEffect <= 3) {
                    setHp(this.hp - 8);
                }else {
                    this.effectDisplay = null;
                }
                break;
        }
        durationOfEffect++;
        if (effect != StatusEffect.Shield && effect != StatusEffect.Stop && durationOfEffect > 3) {
            effect = null;
            System.out.println(name + " no longer has any negative effects");
        }
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getHp() {
        return hp;
    }

    public void setHp(int hp) {
        this.hp = hp;
    }

    public int getAttack() {
        return attack;
    }

    public void setAttack(int attack) {
        this.attack = attack;
    }

    public int getDefense() {
        return defense;
    }

    public void setDefense(int defense) {
        this.defense = defense;
    }

    public int getLevel() {
        return level;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    public int getExp() {
        return exp;
    }

    public void setExp(int exp) {
        this.exp = exp;
    }

    public void setDisable(boolean disable) {
        isDisable = disable;
    }

    public boolean isDisable() {
        return isDisable;
    }

    public int getDamageAfterDefense() {
        return damageAfterDefense;
    }

    public String getEffectDisplay() {
        return effectDisplay;
    }
}
