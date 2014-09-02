#!/usr/bin/env ruby

require('Octokit')

client = Octokit::Client.new(:access_token =>
		'd5d321de78a13e80d6454f95271f096748ce78b1')

user = client.user
puts user
