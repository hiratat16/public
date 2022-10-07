import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { DefaultComponent } from './layouts/default/default.component';
import { HistoriesComponent } from './modules/histories/histories.component';
import { ManagementsComponent } from './modules/managements/managements.component';
import { ProjectsComponent } from './modules/projects/projects.component';
import { TimelinesComponent } from './modules/timelines/timelines.component';
import { WorkingsComponent } from './modules/workings/workings.component';

const routes: Routes = [{
  path: '', component: DefaultComponent,
  children: [
    {path: '', component: ProjectsComponent},
    {path: 'timelines', component: TimelinesComponent},
    {path: 'workings', component: WorkingsComponent},
    {path: 'managements', component: ManagementsComponent},
    {path: 'histories', component: HistoriesComponent}
  ]
}];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
