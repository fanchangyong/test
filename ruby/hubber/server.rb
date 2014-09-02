require 'sinatra'
require 'rest-client'
require 'json'

CLIENT_ID = ENV['GH_BASIC_CLIENT_ID']
CLIENT_SECRET = ENV['GH_BASIC_SECRET_ID']

get '/' do
  erb :index, :locals => {:client_id => CLIENT_ID}
end

get '/callback' do
	session_code = request.env['rack.request.query_hash']['code']
	result = RestClient.post('https://github.com/login/oauth/access_token',
									{:client_id => CLIENT_ID,
									:client_secret => CLIENT_SECRET,
									:code => session_code},
									:accept => :json)
	access_token = JSON.parse(result)['access_token']
	scopes = JSON.parse(result)['scope'].split(',')
	has_user_email_scope = scopes.include? 'user:email'
	puts "has email scope:#{has_user_email_scope}"

	# fetch user information
	auth_result = JSON.parse(RestClient.get('https://api.github.com/user',
																					{:params => 
											{:access_token => access_token}}))

	# if the user authorized it, fetch private emails
	if has_user_email_scope
		auth_result['private_emails'] =
			JSON.parse(RestClient.get('https://api.github.com/user/emails',
																{:params => {:access_token => access_token}}))
			puts "auth_result:#{auth_result}"
		erb :basic, :locals => auth_result
	end
end

