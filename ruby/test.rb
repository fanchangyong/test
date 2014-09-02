#!/usr/bin/ruby

class Car
	def initialize(attrs)
		@name = attrs[:name]
		@brand = attrs[:brand]
	end

	private
	def desc
		puts "Hi,My name is:#{name},my brand is:#{brand}"
	end

	public
	def pub
		puts "putlic method"
	end

	def self.brand_list
		%w{Audi BMW DasAuto Ford Toyota}
	end

	attr_accessor :name,:brand
end

class FordCars < Car
	def my
		pub
	end
end

focus=FordCars.new({
	:name => "Focus",
	:brand => 'ford'
})

puts "Brand list are :#{FordCars.brand_list}"
focus.pub

