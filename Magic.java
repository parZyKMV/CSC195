package YushanoBoken.Model;

public class Magic {
    private MagicType type;
    private String statusEffect;
    private int effect;
    private StatusEffect effectType;
    private int mpCost;

    public Magic(MagicType type){
        if (type == MagicType.Fire){
            this.type = MagicType.Fire;
            mpCost = 5;
            effect = 3;
            statusEffect = "\uD83D\uDD25";
            effectType = StatusEffect.Burn;
        } else if (type == MagicType.Blizzard){
            this.type = MagicType.Blizzard;
            mpCost = 3;
            effect = 2;
            statusEffect = "❄\uFE0F";
            effectType = StatusEffect.Freeze;
        }else if (type == MagicType.Thunder){
            this.type = MagicType.Thunder;
            mpCost = 7;
            effect = 6;
            statusEffect = "⚡";
            effectType = StatusEffect.Paralysis;
        }else if (type == MagicType.Aero){
            this.type = MagicType.Aero;
            mpCost = 10;
            effect = 4;
            statusEffect = "\uD83C\uDF2A\uFE0F";
            effectType = StatusEffect.Shield;
        } else if (type == MagicType.Stop){
            this.type = MagicType.Stop;
            mpCost = 15;
            effect = 0;
            statusEffect = "⌛";
            effectType = StatusEffect.Stop;
        } else if (type == MagicType.Cure){
            this.type = MagicType.Cure;
            mpCost = 20;
            effect = 8;
            statusEffect = "\uD83D\uDC9A";
            effectType = StatusEffect.Heal;
        }
    }

    public int getEffect() {
        return effect;
    }

    public String getStatusEffect() {
        return statusEffect;
    }

    public StatusEffect getEffectType() {
        return effectType;
    }

    public MagicType getType() {
        return type;
    }

    public int getMpCost() {
        return mpCost;
    }
}
