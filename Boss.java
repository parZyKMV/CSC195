package YushanoBoken.Model;

import java.util.Random;

public class Boss extends Character {

    public Boss(BossName name) {
        switch (name){
            case SOLARIAS_IGNIS:
                this.name = "Solarias Ignis";
                this.hp = 40;
                this.attack = 20;
                this.defense = 20;
                this.exp = 25;
                this.abilty = SpecialAbilty.Burning_Pride;
                break;
            case VACORIUS_NEXIS:
                this.name = "Vacorius Nexis";
                this.hp = 60;
                this.attack = 25;
                this.defense = 25;
                this.exp = 30;
                this.abilty = SpecialAbilty.Chains_of_the_Void;
                break;
            case SOLARIAS_ULTIMA:
                this.name = "Solaris Ultima";
                this.hp = 60;
                this.attack = 30;
                this.defense = 30;
                this.exp = 35;
                this.abilty = SpecialAbilty.Unstoppable_Force;
                break;
            case SHIN_GODZILLA:
                this.name = "Shin Godzilla";
                this.hp = 150;
                this.attack = 60;
                this.defense = 60;
                this.exp = 100000;
                this.abilty = SpecialAbilty.Atomic_Ray;
                break;
        }
    }

    protected SpecialAbilty abilty;

    public SpecialAbilty getAbilty() {
        return abilty;
    }

    public boolean isDead(){
        return getHp() <= 0;
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

    public void useSpecialAbility(Hero hero){
       switch (abilty){
           case Burning_Pride:
               int burningPrideAttack = getAttack() * 150 / 100;
               hero.setEffect(StatusEffect.Burn);
               hero.recieveDamage(burningPrideAttack);
               break;
           case Chains_of_the_Void:
                   hero.setDisable(true);
               break;
           case Unstoppable_Force:
               if(getHp() <= 15){
                   this.attack = getAttack() + 6;
                   this.defense = getDefense() + 6;
               }
               break;
           case Atomic_Ray:
               hero.recieveDamage(getAttack() * 2);
               hero.setEffect(StatusEffect.RADIATION);
               hero.setDisable(true);
               break;
       }
    }
}
