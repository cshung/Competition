struct BrowserHistory {
    pages: Vec<String>,
    cur: usize,
    size: usize,
}

impl BrowserHistory {
    fn new(homepage: String) -> Self {
        return BrowserHistory {
            pages: vec![homepage],
            cur: 0,
            size: 1,
        };
    }

    fn visit(&mut self, url: String) {
        if self.cur + 1 < self.pages.len() {
            self.cur = self.cur + 1;
            self.pages[self.cur] = url;
            self.size = self.cur + 1;
        } else {
            self.cur = self.cur + 1;
            self.size = self.size + 1;
            self.pages.push(url);
        }
    }

    fn back(&mut self, steps: i32) -> String {
        let steps = steps as usize;
        if self.cur >= steps {
            self.cur = self.cur - steps;
        } else {
            self.cur = 0;
        }
        return self.pages[self.cur].clone();
    }

    fn forward(&mut self, steps: i32) -> String {
        let steps = steps as usize;
        if self.cur + steps < self.size {
            self.cur = self.cur + steps;
        } else {
            self.cur = self.size - 1;
        }
        return self.pages[self.cur].clone();
    }
}

pub fn design_browser_history() {
    let mut browser_history = BrowserHistory::new("leetcode.com".to_string());
    browser_history.visit("google.com".to_string());
    browser_history.visit("facebook.com".to_string());
    browser_history.visit("youtube.com".to_string());
    println!("{}", browser_history.back(1));
    println!("{}", browser_history.back(1));
    println!("{}", browser_history.forward(1));
    browser_history.visit("linkedin.com".to_string());
    println!("{}", browser_history.forward(2));
    println!("{}", browser_history.back(2));
    println!("{}", browser_history.back(7));
}
