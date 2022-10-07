import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WorkingsComponent } from './workings.component';

describe('WorkingsComponent', () => {
  let component: WorkingsComponent;
  let fixture: ComponentFixture<WorkingsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ WorkingsComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(WorkingsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
