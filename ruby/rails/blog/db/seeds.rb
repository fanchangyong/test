# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the rake db:seed (or created alongside the db with db:setup).
#
# Examples:
#
#   cities = City.create([{ name: 'Chicago' }, { name: 'Copenhagen' }])
#   Mayor.create(name: 'Emanuel', city: cities.first)

Post.create(subject: 'A test', published_at: '01.10.2011')
Post.create(subject: 'Another test', published_at: '01.10.2011')
Post.create(subject: 'And yet one more test', published_at: '02.10.2011')
Post.create(subject: 'Last test', published_at: '01.11.2011')
Post.create(subject: 'Very final test', published_at: '01.11.2012')
