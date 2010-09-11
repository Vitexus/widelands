-- =========================
-- Constructionsite Functionality 
-- =========================
constructionsite_tests = lunit.TestCase("constructionsite tests")
function constructionsite_tests:setup()
   self.f1 = wl.Map():get_field(8,10)
   self.f2 = wl.Map():get_field(12,10)
   self.p = wl.game.Player(1)

   self.p:place_building("lumberjacks_hut", self.f1, true)
   self.p:place_building("fortress", self.f2, true)

   self.l = self.f1.immovable
   self.f = self.f2.immovable
end

function constructionsite_tests:test_upcasting_from_immovable_to_building()
   local i = self.f1.immovable
   assert_equal(i, self.l)
   assert_not_equal(nil, i.building)
end

function constructionsite_tests:teardown()
   pcall(function() self.f1.brn.immovable:remove() end)
   pcall(function() self.f2.brn.immovable:remove() end)
end

function constructionsite_tests:test_name()
   assert_equal("constructionsite", self.l.name)
   assert_equal("constructionsite", self.f.name)
end
function constructionsite_tests:test_type()
   assert_equal("constructionsite", self.l.type)
   assert_equal("constructionsite", self.f.type)
end

function constructionsite_tests:test_size()
   assert_equal("small", self.l.size)
   assert_equal("big", self.f.size)
end

function constructionsite_tests:test_building()
   assert_equal("lumberjacks_hut", self.l.building)
   assert_equal("fortress", self.f.building)
end

