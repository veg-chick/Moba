# **VEGCHICK**

- VEGCHICK
  - 游戏概述与游戏玩法
    - 简介
    - 游戏运行环境要求
    - 游戏支持操作
    - 各单位的属性
  - 装备属性
  - 游戏加载方式
  - 项目安排
   - 项目分工
   - 项目开发流程
  - 评分项完成度
     - 基础功能
     - 进阶功能
     - 更多功能
  - C++的使用
     - C++特性的使用
     - C++11新特性的使用
     - 代码规范

## 游戏概述与游戏玩法

### 简介

VEGCHICK是一款多人在线战术竞技游戏（MOBA），支持最多六人对战，可惜实现局域网下的联机对抗。在游戏中玩家间需要争夺地图上的各种资源并取得等级、经济上的优势，并在保证己方基地不被摧毁的前提下，摧毁敌方基地以获得胜利。

### 游戏运行环境要求：

- 运行平台：Windows
- 最低硬盘空间：20.0G

### 游戏支持操作

|          支持的操作           |   对应的效果   |
| :---------------------------: | :------------: |
|        点击非友方单位         |      攻击      |
|            按下B键            |      回城      |
|            按下Q键            | 释放第一个技能 |
|            按下W键            | 释放第二个技能 |
|            按下E键            | 释放第三个技能 |
|            按下S键            |  停止当前移动  |
|         点击商店按钮          |    打开商店    |
| 在商店中点击装备，之后点击Buy |    购买装备    |

### 各单位属性

（各项数值为相对值）

|  名称  |                击杀奖励                | 攻击力 | 攻击速度 | 生命值 | 护甲 | 魔法抗性 |
| :----: | :------------------------------------: | :----: | :------: | :----: | :--: | :------: |
| 近战兵 |              金币、经验值              |   1    |    1     |   2    |  0   |    0     |
| 远程兵 |              金币、经验值              |   2    |    1     |   1    |  0   |    0     |
| 重甲兵 |              金币、经验值              |   3    |    1     |   3    |  1   |    1     |
| 红BUFF | 金币、经验值、攻击力增益、生命恢复增益 |   4    |    2     |   4    |  2   |    2     |
| 蓝BUFF |       金币、经验值、法力恢复增益       |   4    |    2     |   4    |  2   |    2     |
| Dragon | 金币、经验值、攻击力增益、法术强度增益 |   5    |    2     |   5    |  5   |    5     |

### 装备属性

|   名称   |  长剑  |  短剑   | 十字镐 |  大剑  |  布甲  |  斗篷  |       盾        |      盔甲       | 魔法书 |  法杖  |    拳套    |    披风    |
| :------: | :----: | :-----: | :----: | :----: | :----: | :----: | :-------------: | :-------------: | :----: | :----: | :--------: | :--------: |
| **属性** | 15攻击 | 0.2攻速 | 30攻击 | 60攻击 | 15护甲 | 15魔抗 | 20双抗和200生命 | 50双抗和400生命 | 20法强 | 50法强 | 0.15暴击率 | 0.25暴击率 |
| **售价** |  300   |   300   |  800   |  1500  |  300   |  400   |       700       |      1500       |  500   |  900   |    400     |    800     |

## 游戏加载方式

## 项目安排

### 项目分工

| 姓名   | 分工                               |
| ------ | ---------------------------------- |
| 李玮琦 | AI行为树、UI界面                   |
| 慕林桀 | 服务端、联机、游戏逻辑框架         |
| 南雯瑛 | 各单位模型、动画、粒子特效         |
| 张思璇 | 类设计与实现、属性值设置、装备设计 |

### 项目开发流程



![](C:\Users\aodethri\Documents\Unreal Projects\AMOBAProject\工作流程.png)

## 评分项的完成度

### 基础功能

- [ ] 实现服务端：支持联机对战、电脑AI加入
- [x] 1v1地图
- [x] 支持至少三种英雄类型
- [x] 支持三种基础小兵
- [x] 支持金钱的各种获取方式
- [x] 支持经验、等级系统
- [x] 支持装备系统
- [x] 支持战绩、装备界面查看
- [x] 支持小兵、防御塔AI
- [x] 英雄操作方式参考LOL或Dota

### 进阶功能

- [x] 5v5地图
- [x] 支持更多的英雄类型
- [x] 支持三种野怪
- [ ] 支持聊天

### 更多功能

- [x] 暴击机制
- [x] 生命和法力随时间恢复
- [x] 英雄属性随等级成长
- [x] 技能升级系统
- [x] 野怪、小兵属性随时间成长
- [x] 8秒持续施法后回城
- [x] 英雄状态（沉默、禁锢、晕眩）
- [x] 野怪的特殊击杀奖励
- [x] 冷却缩减
- [x] 小地图实时更新
- [x] 小兵、野怪和防御塔的仇恨机制
- [x] 实现泉水的快速生命恢复和快速击杀闯入的敌方英雄
- [x] 野怪丢失攻击目标后快速生命恢复
- [x] 支持联机的计分板
- [x] 多种伤害类型（物理伤害、魔法伤害、真实伤害）及其伤害减免和治疗效果
- [x] 连杀终结金钱奖励

## C++的使用

### C++特性的使用

1. 类和多态

   - 由Actor派生出BaseActor，由Character派生出BaseCharacter。之后再由BaseActor派生出Crystal和HubCrystal类，由BaseCharacter派生出HeroCharacter、TowerCharacter和WildCharacter类，再由HeroCharacter派生出六个英雄的类
   - HeroCharacter类中的Tick和各Character中的BeginPlay函数都为override函数

2. 迭代器

   ```C++
   for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
   {
   	AMOBAPlayerController* PC = Cast<AMOBAPlayerController>(It->Get());
   	if (PC && PC->IsLocalController())
   	{
   		PC->OnGameOver(SuccessCamp);			
           APlayerController* APC = Cast<APlayerController>(PC);
   		if (APC)
   		{	
               PC->DisableInput(APC);
   		}
   	}
   }
   ```

   FConstplayerControllerIterator是用于获取PlayerController的迭代器

3. 模板

   ```c++
   AMOBAPlayerController* PC = Cast<AMOBAPlayerController>(It->Get());
   ```

   Cast是一个模板函数

4. 类型转换

   ```C++
   switch (static_cast<int>(PackageNumber))
   ```

   将一个float型变量转换为int型变量

### C++11特性的使用

1. 初始化列表

   ```c++
   AMOBACrystalActor(FBaseActorProperty ABaseProperty, FBaseActorValue ABaseValue,CrystalRoad ARoad):AMOBABaseActor(ABaseProperty, ABaseValue), Road(ARoad){} 
   ```

   

2. 类型推断（auto）

   ```c++
   auto MyTimeHanlde = TimeHandles.MpRecoveryTimer;
   ```

   

3. 字符串字面量

   ```C++
   BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
   ```

   

### 代码规范

- 项目代码尽可能地在缩进、命名方面基本遵循了统一和一致的风格（结合自己的书写习惯）
- 项目结构清晰，头文件放在Public目录下，cpp文件放在Private目录下，同一类型的类命名遵循统一规则

