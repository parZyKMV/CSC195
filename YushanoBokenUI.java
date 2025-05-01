package YushanoBoken.View;

import YushanoBoken.Controller.YushanoBokenController;
import YushanoBoken.Model.*;

import java.util.Scanner;

public class YushanoBokenUI {
    private Scanner userInput = new Scanner(System.in);
    private YushanoBokenController controller = new YushanoBokenController();
    private int turn;
    private Hero hero;

    public void run(){
        System.out.println("====== WELCOME TO YUSHANO BOKEN =======\n");
        System.out.println("Please chose one of the next Heroes");
        showHeroes();
        HeroName heroName = choseAHero();
        hero = new Hero(heroName);
        System.out.println("You chose " + heroName + "\n");
        turn = controller.startGame(hero);
        while (!hero.isDead()){
            if(turn == 0){
                updateHeroStats(hero);
                showOptions();
                Option option = choseAOption();
            turn = controller.HeroTurn(option);
            } else if (turn == 1) {
                turn = controller.EnemiesTurn();
            }
        }
        System.out.println("GAME OVER!");
        System.out.println("Do you want to play again? (Yes/No)");
        String answer = userInput.nextLine();
        if (answer.equalsIgnoreCase("Yes")) {
            run();
        }else if (answer.equalsIgnoreCase("No")) {
            System.exit(0);
        }
    }

    public void showHeroes(){
        System.out.println("=========================================");
        System.out.println("             🏆 CHOOSE YOUR HERO 🏆");
        System.out.println("=========================================");

        StringBuilder heroes = new StringBuilder();

        heroes.append("1️⃣  🛡️ Hero: **Galahad**\n");
        heroes.append("   ❤️ Health: 20\n");
        heroes.append("   ⚔️ Attack: 6\n");
        heroes.append("   🛡️ Defense: 6\n");
        heroes.append("=========================================\n");

        heroes.append("2️⃣  ⚔️ Hero: **Balin**\n");
        heroes.append("   ❤️ Health: 15\n");
        heroes.append("   ⚔️ Attack: 7\n");
        heroes.append("   🛡️ Defense: 7\n");
        heroes.append("=========================================\n");

        heroes.append("3️⃣  🏹 Hero: **Elaine**\n");
        heroes.append("   ❤️ Health: 25\n");
        heroes.append("   ⚔️ Attack: 5\n");
        heroes.append("   🛡️ Defense: 5\n");
        heroes.append("=========================================\n");

        System.out.println(heroes);
    }

    public HeroName choseAHero(){
        String choice = userInput.nextLine();
        return heroName(choice);
    }

    public HeroName heroName(String choice){
        int optionIndex = 0;
        try {
            optionIndex = Integer.parseInt(choice);
        }catch (NumberFormatException e){
            System.out.println("Please enter a valid option!");
            return choseAHero();
        }
        HeroName[] options = HeroName.values();
        try {
            return options[optionIndex - 1];
        }catch (IndexOutOfBoundsException e){
            System.out.println("Please enter a valid option!");
            System.out.println("Enter a number between 1 and " + options.length + ".");
            return choseAHero();
        }
    }

    public void showOptions(){
        System.out.println("=========================================");
        System.out.println("            🔥 OPTIONS 🔥");
        System.out.println("=========================================");
        System.out.println("1️⃣  Attack ⚔️");
        System.out.println("2️⃣  Use Item 🧪");
        if (hero.getLevel() >= 2){
            System.out.println("3️⃣  Magic ✨");
        }
        System.out.println("=========================================");
    }

    public Option choseAOption(){
        String option = userInput.nextLine();
        return chosenOption(option);
    }

    public Option chosenOption(String option){
        int optionIndex = 0;
        try {
            optionIndex = Integer.parseInt(option);
        }catch (NumberFormatException e){
            System.out.println("Please enter a valid option!");
            return choseAOption();
        }
        Option[] options = Option.values();
        try {
            return options[optionIndex - 1];
        }catch (IndexOutOfBoundsException e){
            System.out.println("Please enter a valid option!");
            System.out.println("Enter a number between 1 and " + options.length + ".");
            return choseAOption();
        }
    }

    public void updateHeroStats(Hero hero){
        StringBuilder stats = new StringBuilder();
        stats.append("=========================================\n");
        stats.append("          🛡️ HERO STATUS 🛡️       \n");
        stats.append("=========================================\n");
        stats.append("👤 Name: " + hero.getName() + "\n");
        stats.append("⭐ Level: " + hero.getLevel() + "\n");
        stats.append("❤️ HP: " + hero.getHp() + "/" + hero.getMaxHeroHp() + "\n");
        stats.append("🔷 MP: " + hero.getMp() + "\n");
        stats.append("⚔️ Attack: " + hero.getAttack() + "\n");
        stats.append("🛡️ Defense: " + hero.getDefense() + "\n");
        stats.append("🔺 EXP: " + hero.getExp() + "\n");
        System.out.println(stats);
    }

}
