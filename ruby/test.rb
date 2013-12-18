#!/usr/bin/env ruby


puts "Input some text:"
text=gets.chomp

puts "Input redact:";
redact=gets.chomp();

words=text.split(" ");
puts("words is:#{words}");

words.each do |w|
	puts w
end
