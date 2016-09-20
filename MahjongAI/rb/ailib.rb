

class Player
  attr_reader :tehai, :kawahai, :naki_mentsu
  attr_accessor :mentsu, :anpai, :kikenhai, :pai_kukan
  
  def initialize(tehai = [], kawahai = [], naki_mentsu = [])
    @tehai = tehai
    @kawahai = kawahai
    @naki_mentsu = naki_mentsu
  end
end

class Mentsu
  TYPE_SHUNTSU = 1
  TYPE_KOUTSU = 2
  TYPE_MINKAN = 3
  TYPE_ANKAN = 4
  TYPE_ATAMA = 5
  
  attr_reader :type, :num
  attr_accessor :weight
  
  def initialize(type=TYPE_SHUNTSU, num=0)
    @type = type
    @num = num
  end
  
  def kiken(pais)
    case @type
    when TYPE_SHUNTSU
      pais[@num-1] += 0.1 if (@num % 9) > 0
      pais[@num] += 0.2
      pais[@num+1] += 0.1
      pais[@num+2] += 0.2
      pais[@num+3] += 0.1 if (@num % 9) < 6
    when TYPE_KOUTSU
      pais[@num] += 0.05
    when TYPE_ATAMA
      pais[@num] += 0.1
    end
  end
  
  def weight(pai_kukan)
    case @type
    when TYPE_SHUNTSU
      return (pai_kukan[@num] * pai_kukan[@num+1] * pai_kukan[@num+2]).to_i
    when TYPE_KOUTSU
      return 4 if pai_kukan[@num] == 4
      return 1 if pai_kukan[@num] == 3
      return 0
    when TYPE_ATAMA
      return 6 if pai_kukan[@num] == 4
      return 3 if pai_kukan[@num] == 3
      return 1 if pai_kukan[@num] == 2
      return 0
    end
  end
  
  def self.all
    ret = []
    0.upto 8 do |n|
      ret.push(Mentsu.new(TYPE_SHUNTSU, n))
      ret.push(Mentsu.new(TYPE_SHUNTSU, n+9))
      ret.push(Mentsu.new(TYPE_SHUNTSU, n+18))
    end
    0.upto 33 do |n|
      ret.push(Mentsu.new(TYPE_KOUTSU, n))
    end
    ret
  end
  
  def self.all_atama
    ret = []
    0.upto 33 do |n|
      ret.push(Mentsu.new(TYPE_ATAMA, n))
    end
    ret
  end
  
  
  def sub(haiarray)
    case @type
    when TYPE_SHUNTSU
      haiarray[@num] -= 1
      haiarray[@num+1] -= 1
      haiarray[@num+2] -= 1
    when TYPE_ATAMA
      haiarray[@num] -= 2
    when TYPE_KOUTSU
      haiarray[@num] -= 3
    when TYPE_MINKAN, TYPE_ANKAN
      haiarray[@num] -= 4
    end
  end
  
end

class Pai
  attr_reader :num, :aka, :naki, :riichi
  
  def initialize(num=0, aka=false, naki = false, riichi = false)
    @num = num
    @aka = aka
    @naki = naki
    @riichi = riichi
  end
  
  def getDoraHyouji
    if @num < 27
      if @num % 9 == 0
        return @num + 8
      else
        return @num - 1
      end
    elsif @num == 27
      return 30
    elsif @num == 31
      return 33
    else
      return @num - 1
    end
  end
  
end

class Array
  def w_sample
    self.size.times.map do |i|
      Array.new(yield(self[i]), self[i])
    end.flatten.sample
  end
end



class MJ0
  SIMU_SIZE=5000
  
  def self.simulate(players, myself, doras)
    _nokorihai = Array.new(34, 4.0)
    pai_kukan = Array.new(34, 0.0)
    
    (players + [myself]).each do |player| 
      player.anpai = Array.new(34, false)
      player.kikenhai = Array.new(34, 0.0)
      player.tehai.each { |hai| _nokorihai[hai.num] -= 1 }
      
      player.kawahai.each do |hai|
        _nokorihai[hai.num] -= 1 unless hai.naki
        player.anpai[hai.num] = true
      end
      player.naki_mentsu.each { |m| m.sub(_nokorihai) }
      player.mentsu = []
    end
    
    myself.kikenhai = Array.new(34, 0.0)
    
    doras.each { |dora| _nokorihai[dora.getDoraHyouji] -= 1 }
    
    SIMU_SIZE.times do
      (players + [myself]).each do |player|
        player.pai_kukan = _nokorihai.clone
        # TODO 手読みで牌空間を変える
      end
      
      while !(subjects = players.select { |player| player.naki_mentsu.size + player.mentsu.size < 4 }).empty?
        subjects.each do |player|
          # メンツをランダムで抽出する
          mentsu = Mentsu.all.w_sample { |m| m.weight(player.pai_kukan) }
          player.mentsu.push(mentsu)
          # メンツを構成する牌を牌空間から除去する
          (players + [myself]).each { |p2| mentsu.sub(p2.pai_kukan) }
          # 危険度を更新する
          mentsu.kiken(myself.kikenhai)
        end
      end
      
      players.each do |player|
        # 頭をランダムで抽出する
        mentsu = Mentsu.all_atama.w_sample { |m| m.weight(player.pai_kukan) }
        player.mentsu.push(mentsu)
        # メンツを構成する牌を牌空間から除去する
        (players + [myself]).each { |p2| mentsu.sub(p2.pai_kukan) }
        # 危険度を更新する
        mentsu.kiken(myself.kikenhai)
      end
    
      pai_kukan.each_with_index { |pai, idx| pai_kukan[idx] += myself.pai_kukan[idx] }
    end
    myself.pai_kukan = pai_kukan.map { |pai| pai / SIMU_SIZE }
    myself.kikenhai.map! { |pai| pai / SIMU_SIZE }
  end
end

def p(num)
  Pai.new(num)
end

def pais(a)
  a.map { |n| Pai.new(n) }
end

enemies = [ Player.new, Player.new, Player.new ]
player = Player.new(pais([0, 1, 2, 2, 3, 5, 7, 9, 14, 14, 15, 20, 23, 25]))

MJ0.simulate(enemies, player, [p(15)])

puts player.inspect
