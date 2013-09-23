#!/usr/bin/ruby

file = $stdin.read

while file =~ /x="([0-9]*\.(.*))"/ do
   n = $1.to_i
   n2 = n + 200 
   d = $2
   file = file.sub(/x="#{n.to_s}\.(.*)"/,"quapzango=\"#{n2}.#{d}\"") 
end
while file =~ /x="([0-9]*)"/ do
   n = $1.to_i
   n2 = n + 200 
   file = file.sub(/x="#{n.to_s}"/,"quapzango=\"#{n2}\"") 
end



file = file.gsub(/quapzango/,"x")
puts file

