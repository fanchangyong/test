class GameController < ApplicationController
  def ping
		logger.info '+++ Example +++'
		redirect_to :action => 'pong'
  end

  def pong
  end
end
