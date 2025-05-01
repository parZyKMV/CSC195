package YushanoBoken.Controller;

import YushanoBoken.Model.*;
import YushanoBoken.View.Option;

import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class YushanoBokenController{
    private Scanner userInput = new Scanner(System.in);
    private int turn = 0;
    private Enemy enemy;
    private Hero hero;
    private Boss boss;
    private int level = 1;
    private ArrayList<BossName> bosses = new ArrayList<>();


    public int startGame(Hero hero) {
        this.hero = hero;
        generateEnemiesOrBoss();
        presentEnemyOrBoss();
        bosses.clear();
        return turn = 0;
    }

    public int HeroTurn(Option option){
        if(hero.isDisable()){
            return turn = 1;
        }
        if(option == Option.Attack){
            if (enemy != null) {
                enemy.recieveDamage(hero.getAttack());
                if (enemy.isDead()){
                    defeatEnemy(enemy);
                    return turn = 0;
                }
            } else if (boss != null) {
                boss.recieveDamage(hero.getAttack());
                if (boss.isDead()){
                    defeatBoss(boss);
                    return turn = 0;
                }
            }
        } else if (option == Option.Use_Item){
            useItem();
        } else if (option == Option.Magic){
            useMagic();
        }
        return turn = 1;
    }

    private void defeatEnemy(Enemy enemy) {
        System.out.println("+++" + enemy.getName() + " iS DEAD +++ \n");
        Item item = enemy.dropLoot();
        hero.addItem(item);
        System.out.println("===You receive " + item + "===");
        hero.levelUp(enemy.getExp());
        System.out.println("===You got " + enemy.getExp() + " exp===");
        this.enemy = null;
        generateEnemiesOrBoss();
        presentEnemyOrBoss();
    }

    private void defeatBoss(Boss boss) {
        Item item = boss.dropLoot();
        hero.addItem(item);
        System.out.println("======You receive " + item + "=====");
        hero.levelUp(boss.getExp());
        System.out.println("======You got " + boss.getExp() + " exp ======");
        System.out.println("CONGRATULATIONS \nYou have defeated " + boss.getName() + "\n");
        this.boss = null;
        generateEnemiesOrBoss();
        presentEnemyOrBoss();
    }

    private void useItem() {
        boolean isInventoryEmpty = hero.displayInventory();
        if (isInventoryEmpty) {
            System.out.println("Chose an item # \n");
            Item item = choseAOption();
            hero.useItem(item);
        } else {
            System.out.println("You don't have items in your inventory \n");
        }
    }

    private void useMagic() {
        boolean isMagicEmpty = hero.displayMagic();
        if (!isMagicEmpty) {
            System.out.println("You have no magic available.");
            return;
        }
        System.out.println("Select a magic: ");
        int option = userInput.nextInt() - 1;
        if (option >= 0 && option < hero.getMagic().size()) {
            Magic magia = hero.getMagic().get(option);
            if (hero.getMp() >= magia.getMpCost()) {
                hero.setMp(hero.getMp() - magia.getMpCost());
                System.out.println(hero.getName() + " use " + magia.getType());
                if(magia.getType() == MagicType.Cure || magia.getType() == MagicType.Aero){
                    hero.setEffect(magia.getEffectType());
                }else{
                    if (enemy != null) {
                        enemy.recieveDamage(magia.getEffect());
                        enemy.setEffect(magia.getEffectType());
                        if (enemy.isDead()) {
                            defeatEnemy(enemy);
                        }
                    } else if (boss != null) {
                        boss.recieveDamage(magia.getEffect());
                        boss.setEffect(magia.getEffectType());
                        if (boss.isDead()) {
                            defeatBoss(boss);
                        }
                    }
                }
            } else {
                System.out.println("You don't have enough MP.");
            }
        } else {
            System.out.println("Invalid option.");
        }
    }

    public Item choseAOption(){
        String option = userInput.nextLine();
        return chosenOption(option);
    }

    public Item chosenOption(String option) {
        int optionIndex = 0;
        try {
            optionIndex = Integer.parseInt(option);
        } catch (NumberFormatException e) {
            System.out.println("Please enter a valid number!");
            return choseAOption();
        }
        Inventory heroInventory = hero.getInventory();
        ArrayList<Item> items = heroInventory.getItems();
        if (optionIndex < 1 || optionIndex > items.size()) {
            System.out.println("Please enter a valid option!");
            System.out.println("Enter a number between 1 and " + items.size() + ".");
            return choseAOption();
        }

        return items.get(optionIndex - 1);
    }

    public int EnemiesTurn(){
        if (enemy != null) {
            enemy.applyStatusEffect();
            if (enemy.isDisable()){
                updateEnemyAndBossHealth();
                return 0;
            }
            updateEnemyAndBossHealth();
            if(enemy.isDead()){
                defeatEnemy(enemy);
                return 0;
            }
            hero.recieveDamage(enemy.getAttack());
            System.out.println("++++YOU HAVE RECEIVED " + hero.getDamageAfterDefense() + " DAMAGE+++++");
            return turn = 0;
        } else if (boss != null) {
            boss.applyStatusEffect();
            if (boss.isDisable()){
                updateEnemyAndBossHealth();
                return 0;
            }
            updateEnemyAndBossHealth();
            if(boss.isDead()){
                defeatBoss(boss);
                return 0;
            }
            Random rand = new Random();
            int useSpecialAbility = rand.nextInt(3) + 1;
            if (useSpecialAbility == 3) {
                boss.useSpecialAbility(hero);
                System.out.println("++++++" + boss.getName() + " USE " + boss.getAbilty() + " SPECIAL+++++");
            } else {
                hero.recieveDamage(boss.getAttack());
                System.out.println("+++++YOU HAVE RECEIVED " + hero.getDamageAfterDefense() + " DAMAGE++++++");
            }
        }
        return turn = 0;
    }

    public void generateEnemiesOrBoss() {
        if (enemy == null || boss == null || enemy.isDead() || boss.isDead()) {
            Random rand = new Random();
            int generateEnemiesOrBoss = rand.nextInt(5) + 1;
            if (hero.getLevel() >= 10 && generateEnemiesOrBoss >= 4) {
                generateBossBasedOnLevel();
            } else {
                generateRandomEnemy();
            }
        }
    }

    private void generateBossBasedOnLevel() {
        int heroLevel = hero.getLevel();
        if (heroLevel >= 10 && heroLevel <= 20) {
            generateBoss(BossName.SOLARIAS_IGNIS);
        } else if (heroLevel >= 21 && heroLevel <= 30) {
            generateBoss(BossName.VACORIUS_NEXIS);
        } else if (heroLevel >= 31 && heroLevel <= 40) {
            generateBoss(BossName.SOLARIAS_ULTIMA);
        } else if (heroLevel >= 50 && heroLevel <= 100) {
            generateBoss(BossName.SHIN_GODZILLA);
        }
    }

    private void generateBoss(BossName bossName) {
        if (bosses.contains(bossName)) {
            generateRandomEnemy();
        } else {
            boss = new Boss(bossName);
            bosses.add(bossName);
        }
    }

    private void generateRandomEnemy() {
        Random rand = new Random();
        EnemyType[] enemyTypes = EnemyType.values();
        int enemies = rand.nextInt(enemyTypes.length);
        this.enemy = new Enemy(enemyTypes[enemies]);
        if (hero.getLevel() >= 6) {
            enemy.levelUp(getLevel());
            setLevel(getLevel() + 1);
        }
    }

    public void setLevel(int level){
        this.level = level;
    }

    public int getLevel(){
        return level;
    }

    public void updateEnemyAndBossHealth(){
        StringBuilder hp = new StringBuilder();
        if (enemy != null) {
            hp.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            hp.append("        ⚔️ ENEMY IN COMBAT ⚔️\n");
            hp.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            hp.append("👹 Name: " + enemy.getName() + "\n");
            hp.append("❤️ HP: " + enemy.getHp() + "\n");
            if(enemy.getEffectDisplay() != null){
                hp.append("✨ Status: " + enemy.getEffectDisplay() +"\n");
            }
            hp.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        } else if (boss != null) {
            hp.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            hp.append("       ⚠️ BOSS IN COMBAT ⚠️\n");
            hp.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            hp.append("👿 Name: " + boss.getName() + "\n");
            hp.append("❤️ HP: " + boss.getHp() + "\n");
            if(boss.getEffectDisplay() != null){
                hp.append("✨ Status: " + boss.getEffectDisplay() +"\n");
            }
            hp.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        }
        System.out.println(hp);
    }

    public void presentEnemyOrBoss(){
        StringBuilder displayEnemyInfo = new StringBuilder();
        if (enemy != null) {
            displayEnemyInfo.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            displayEnemyInfo.append("         AN ENEMY HAS APPEARED           \n");
            displayEnemyInfo.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            displayEnemyInfo.append("        ⚔️ ENEMY IN COMBAT ⚔️\n");
            displayEnemyInfo.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            displayEnemyInfo.append("👹 Name: " + enemy.getName() + "\n");
            displayEnemyInfo.append("❤️ HP: " + enemy.getHp() + "\n");
            displayEnemyInfo.append("⚔️ Attack: " + enemy.getAttack() + "\n");
            displayEnemyInfo.append("🛡️ Defense: " + enemy.getDefense() + "\n");
            displayEnemyInfo.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        } else if (boss != null){
            displayEnemyInfo.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            displayEnemyInfo.append("       ⚠️⚠️⚠️⚠️DANGER⚠️⚠️⚠️⚠️          \n");
            displayEnemyInfo.append("         AN BOSS HAS APPEARED            \n");
            displayEnemyInfo.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            displayEnemyInfo.append("       ⚠️ BOSS IN COMBAT ⚠️\n");
            displayEnemyInfo.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            displayEnemyInfo.append("👿 Name: " + boss.getName() + "\n");
            displayEnemyInfo.append("❤️ HP: " + boss.getHp() + "\n");
            displayEnemyInfo.append("⚔️ Attack: " + boss.getAttack() + "\n");
            displayEnemyInfo.append("🛡️ Defense: " + boss.getDefense() + "\n");
            displayEnemyInfo.append("⚡ Special Ability: " + boss.getAbilty() + "\n");
            displayEnemyInfo.append("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        }
        System.out.println(displayEnemyInfo);
    }

}
