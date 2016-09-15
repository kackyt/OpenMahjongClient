

class Player
  attr_reader :tehai, :kawahai, :naki_mentsu
  attr_accessor :mentsu, :anpai, :kikenhai, :pai_kukan
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
      return pai_kukan[@num] * pai_kukan[@num+1] * pai_kukan[@num+2]
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
      ret.push(Mentsu.new(TYPE_SHUNTSU, n)
      ret.push(Mentsu.new(TYPE_SHUNTSU, n+9)
      ret.push(Mentsu.new(TYPE_SHUNTSU, n+18)
    end
    0.upto 33 do |n|
      ret.push(Mentsu.new(TYPE_KOUTSU, n)
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

class hai
  attr_reader :num, :aka, :naki, :riichi
  
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
  def sample
    self.size.times.map do |i|
      Array.new(yield(self[i]), self[i])
    end.flatten.sample(n)
  end
end



class MJ0
  attr_reader :nokorihai
  SIMU_SIZE=10000
  
  def simulate(players, doras)
    @nokorihai = Array.new(34, 4.0)
    @kikenhai = Array.new(34, 0.0)
    _nokorihai = Array.new(34, 4.0)
    
    players.each do |player| 
      player.anpai = Array.new(34, false)
      player.kikenhai = Array.new(34, 0.0)
      player.kawahai.each do |hai|
        _nokorihai[hai.num] -= 1 unless hai.naki
        player.anpai[hai.num] = true
      end
      player.naki_mentsu.each { |m| m.sub(_nokorihai) }
      player.mentsu = []
    end
    
    doras.each { |dora| _nokorihai[dora.getDoraHyouji] -= 1 }
    
    SIMU_SIZE.times do
      players.each do |player|
        player.pai_kukan = Array.new(_nokorihai)
        # TODO 手読みで牌空間を変える
      end
      
      until (subjects = players.select { |player| player.naki_mentsu.size + player.mentsu.size < 4 }).empty?
      do
        subjects.each do |player|
          mentsu = Mentsu.all.sample { |m| m.weight(player.pai_kukan) }
          player.mentsu.push(mentsu)
          players.each { |p2| mentsu.sub(p2.pai_kukan) }
          mentsu.kiken(players.kikenhai)
        end
      end
      
      players.each do |player|
      end
    end
      
  end

end





module AILib
  extend self
  def get_tsumogiri
    12
  end
end
