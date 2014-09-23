require 'test_helper'

class HomeControllerTest < ActionController::TestCase
  test "should get index" do
    get :index
    assert_response :success
  end

  test "should get ping" do
    get :ping
    assert_response :success
  end

  test "should get pong" do
    get :pong
    assert_response :success
  end

end
